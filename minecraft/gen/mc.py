# https://minecraft.fandom.com/wiki/Region_file_format
# https://minecraft.wiki/w/NBT_format#Binary_format
# https://minecraft.wiki/w/Chunk_format/McRegion

import sys
import struct
from pprint import pprint
import zlib
import enum
from dataclasses import dataclass
from itertools import chain

def _parse_locations(mem, offset):
    for i in range(1024):
        ix = offset + i * 4
        chunk_location, = struct.unpack(">I", mem[ix:ix+4])
        chunk_offset = (chunk_location >> 8) & 0xffffff
        chunk_sector_count = chunk_location & 0xff
        yield chunk_offset, chunk_sector_count

def parse_locations(mem, offset):
    locations = list(_parse_locations(mem, offset))
    return offset + 1024 * 4, locations

def _parse_timestamps(mem, offset):
    for i in range(1024):
        ix = offset + i * 4
        timestamp, = struct.unpack(">I", mem[ix:ix+4])
        yield timestamp

def parse_timestamps(mem, offset):
    timestamps = list(_parse_timestamps(mem, offset))
    return offset + 1024 * 4, timestamps

def print_locations(locations):
    for y in range(32):
        for x in range(32):
            offset, count = locations[y * 32 + x]
            print(str(offset).rjust(4), end=' ')
        print()

class CountZeroException(Exception):
    pass

def parse_payload(mem, location):
    offset, count = location
    if count == 0:
        raise CountZeroException()
    ix = offset * 4096
    payload = mem[ix:ix + count * 4096]
    length, = struct.unpack(">I", payload[0:4])
    assert length <= count * 4096, (length, count)
    compression_type = payload[4]
    data = payload[5:5 + (length - 1)]
    assert compression_type == 2, compression_type
    uncompressed = zlib.decompress(data)
    return memoryview(uncompressed)

class TAG:
    Byte = 0x01
    Short = 0x02
    Int = 0x03
    Long = 0x04
    Float = 0x05
    Double = 0x06
    ByteArray = 0x07
    String = 0x08
    List = 0x09
    Compound = 0x0a

@dataclass
class Byte:
    name: str
    value: int

@dataclass
class Short:
    name: str
    value: int

@dataclass
class Int:
    name: str
    value: int

@dataclass
class Long:
    name: str
    value: int

@dataclass
class Float:
    name: str
    value: float

@dataclass
class Double:
    name: str
    value: float

@dataclass
class ByteArray:
    name: str
    value: bytes

@dataclass
class String:
    name: str
    value: str

@dataclass
class List:
    name: str
    items: list

@dataclass
class Compound:
    name: str
    tags: list

def indent(level):
    return "  " * level

def parse_tag_inner(mem, offset, level, tag_type, name):
    payload = mem[offset:]
    if tag_type == TAG.Byte:
        value, = struct.unpack(">b", payload[0:1])
        return offset + 1, Byte(name, value)
    if tag_type == TAG.Short:
        value, = struct.unpack(">h", payload[0:2])
        return offset + 2, Short(name, value)
    elif tag_type == TAG.Int:
        value, = struct.unpack(">i", payload[0:4])
        return offset + 4, Int(name, value)
    elif tag_type == TAG.Long:
        value, = struct.unpack(">q", payload[0:8])
        return offset + 8, Long(name, value)
    elif tag_type == TAG.Float:
        value, = struct.unpack(">f", payload[0:4])
        return offset + 4, Float(name, value)
    elif tag_type == TAG.Double:
        value, = struct.unpack(">d", payload[0:8])
        return offset + 8, Double(name, value)
    elif tag_type == TAG.ByteArray:
        size, = struct.unpack(">i", payload[0:4])
        value = bytes(payload[4:4+size])
        return offset + 4 + size, ByteArray(name, value)
    elif tag_type == TAG.String:
        size, = struct.unpack(">H", payload[0:2])
        value = bytes(payload[2:2+size]).decode('utf-8')
        return offset + 2 + size, String(name, value)
    elif tag_type == TAG.List:
        list_content_tag_id, size = struct.unpack(">BI", payload[0:5])
        items = []
        offset = offset + 5
        for i in range(size):
            payload = mem[offset:]
            offset, item = parse_tag_inner(mem, offset, level, list_content_tag_id, None)
            items.append(item)
        return offset, List(name, items)
    elif tag_type == TAG.Compound:
        tags = []
        while payload[0] != 0:
            offset, tag = parse_tag(mem, offset, level+1)
            payload = mem[offset:]
            tags.append(tag)
        return offset + 1, Compound(name, tags)
    else:
        assert False, tag_type

def parse_tag(mem, offset, level):
    data = mem[offset:]
    tag_type = data[0]
    name_length, = struct.unpack(">H", data[1:3])
    name = bytes(data[3:3+name_length])
    #print(indent(level), tag_type, name_length, name)
    offset = offset + 3 + name_length
    return parse_tag_inner(mem, offset, level, tag_type, name)

@dataclass
class Level:
    blocks: bytes
    data: bytes
    sky_light: bytes
    block_light: bytes
    height_map: bytes
    x_pos: int
    z_pos: int

def level_from_tag(tag):
    assert type(tag) == Compound
    assert tag.name == b''
    assert len(tag.tags) == 1
    level, = tag.tags
    assert type(level) == Compound
    assert level.name == b'Level'

    name_mapping = {
        b'Blocks': 'blocks',
        b'Data': 'data',
        b'SkyLight': 'sky_light',
        b'BlockLight': 'block_light',
        b'HeightMap': 'height_map',
        b'xPos': 'x_pos',
        b'zPos': 'z_pos',
    }

    args = {}

    for tag in level.tags:
        if tag.name in name_mapping:
            arg_name = name_mapping[tag.name]
            args[arg_name] = tag.value

    return Level(**args)

def parse_location(mem, location):
    uncompressed = parse_payload(mem, location)
    offset, tag = parse_tag(uncompressed, 0, 0)
    assert offset == len(uncompressed), (offset, len(uncompressed))
    level = level_from_tag(tag)
    return level

def xyz_from_block_index(block_index):
    assert block_index >= 0 and block_index < (128 * 16 * 16)
    x = int(block_index / (128 * 16))
    y = int(block_index % 128)
    z = int(int(block_index / 128) % 16)
    return x, y, z

def block_index_from_xyz(x, y, z):
    assert x >= 0 and x < 16
    assert y >= 0 and y < 128
    assert z >= 0 and z < 16
    return int(y + z * 128 + x * 128 * 16)

def wrap_n(nc, chunk_c):
    if nc < 0:
        nc = 15
        chunk_c = chunk_c - 1
    if nc > 15:
        nc = 0
        chunk_c = chunk_c + 1
    return nc, chunk_c

def vec3_add(v1, v2):
    return (
        v1[0] + v2[0],
        v1[1] + v2[1],
        v1[2] + v2[2],
    )

def vec3_mul(v, s):
    return (
        v[0] * s,
        v[1] * s,
        v[2] * s,
    )

vertex_table = [
    ((-1.0, 1.0, -1.0), (0.0, 1.0, 0.0), (1.0, 0.0)),
    ((1.0, 1.0, 1.0), (0.0, 1.0, 0.0), (0.0, 1.0)),
    ((1.0, 1.0, -1.0), (0.0, 1.0, 0.0), (0.0, 0.0)),
    ((1.0, 1.0, 1.0), (0.0, 0.0, 1.0), (1.0, 1.0)),

    ((-1.0, -1.0, 1.0), (0.0, 0.0, 1.0), (0.0, 0.0)),
    ((1.0, -1.0, 1.0), (0.0, 0.0, 1.0), (1.0, 0.0)),
    ((-1.0, 1.0, 1.0), (-1.0, 0.0, 0.0), (1.0, 1.0)),
    ((-1.0, -1.0, -1.0), (-1.0, 0.0, 0.0), (0.0, 0.0)),

    ((-1.0, -1.0, 1.0), (-1.0, 0.0, 0.0), (1.0, 0.0)),
    ((1.0, -1.0, -1.0), (0.0, -1.0, 0.0), (1.0, 0.0)),
    ((-1.0, -1.0, 1.0), (0.0, -1.0, 0.0), (0.0, 1.0)),
    ((-1.0, -1.0, -1.0), (0.0, -1.0, 0.0), (0.0, 0.0)),

    ((1.0, 1.0, -1.0), (1.0, 0.0, 0.0), (1.0, 1.0)),
    ((1.0, -1.0, 1.0), (1.0, 0.0, 0.0), (0.0, 0.0)),
    ((1.0, -1.0, -1.0), (1.0, 0.0, 0.0), (1.0, 0.0)),
    ((-1.0, 1.0, -1.0), (0.0, 0.0, -1.0), (1.0, 1.0)),
    ((1.0, -1.0, -1.0), (0.0, 0.0, -1.0), (0.0, 0.0)),
    ((-1.0, -1.0, -1.0), (0.0, 0.0, -1.0), (1.0, 0.0)),
    ((-1.0, 1.0, 1.0), (0.0, 1.0, 0.0), (1.0, 1.0)),
    ((-1.0, 1.0, 1.0), (0.0, 0.0, 1.0), (0.0, 1.0)),
    ((-1.0, 1.0, -1.0), (-1.0, 0.0, 0.0), (0.0, 1.0)),
    ((1.0, -1.0, 1.0), (0.0, -1.0, 0.0), (1.0, 1.0)),
    ((1.0, 1.0, 1.0), (1.0, 0.0, 0.0), (0.0, 1.0)),
    ((1.0, 1.0, -1.0), (0.0, 0.0, -1.0), (0.0, 1.0))
]

faces_by_normal = {
    (-1.0, 0.0, 0.0): [6, 7, 8, 6, 20, 7],
    (0.0, -1.0, 0.0): [9, 10, 11, 9, 21, 10],
    (0.0, 0.0, -1.0): [15, 16, 17, 15, 23, 16],
    (0.0, 0.0, 1.0): [3, 4, 5, 3, 19, 4],
    (0.0, 1.0, 0.0): [0, 1, 2, 0, 18, 1],
    (1.0, 0.0, 0.0): [12, 13, 14, 12, 22, 13]
}

vertex_buffer = {}

def add_vertex(vertex):
    if vertex in vertex_buffer:
        return vertex_buffer[vertex]
    else:
        index = len(vertex_buffer)
        vertex_buffer[vertex] = index
        return index

def emit_face(center_position, block_id, triangles):
    for index in triangles:
        position, normal, texture = vertex_table[index]
        position = vec3_add(vec3_mul(position, 0.5), center_position)
        vertex = (position, normal, texture, block_id)
        new_index = add_vertex(vertex)
        yield new_index

def block_neighbors(level_table, chunk_x, chunk_z, block_index):
    block_id = level_table[(chunk_x, chunk_z)].blocks[block_index]
    if block_id == 0:
        return

    def neighbor_exists(nx, ny, nz):
        if ny > 127 or ny < 0:
            return False
        nx, n_chunk_x = wrap_n(nx, chunk_x)
        nz, n_chunk_z = wrap_n(nz, chunk_z)
        if nx > 15 or nx < 0:
            return True
        if nz > 15 or nz < 0:
            return True
        n_block_index = block_index_from_xyz(nx, ny, nz)
        key = (n_chunk_x, n_chunk_z)
        if key not in level_table:
            return True
        n_block_id = level_table[key].blocks[n_block_index]
        return n_block_id != 0

    x, y, z = xyz_from_block_index(block_index)

    center_position = vec3_add((x, y, z), (chunk_x * 16, 0, chunk_z * 16))

    for normal, triangles in faces_by_normal.items():
        neighbor = vec3_add(normal, (x, y, z))
        if not neighbor_exists(*neighbor):
            yield from emit_face(center_position, block_id, triangles)

            #yield chunk_x, chunk_z, block_index, block_id
            #break

def devoxelize_region(level_table):
    for chunk_x, chunk_z in level_table.keys():
        for block_index in range(128 * 16 * 16):
            yield from block_neighbors(level_table, chunk_x, chunk_z, block_index)

from collections import defaultdict
counts = defaultdict(int)

def linearized_vertex_buffer():
    for vertex, i in sorted(vertex_buffer.items(), key=lambda kv: kv[1]):
        yield vertex

def main(mcr_path, data_path):
    with open(mcr_path, "rb") as f:
        buf = f.read()
    mem = memoryview(buf)

    offset = 0
    offset, locations = parse_locations(mem, offset)
    offset, timestamps = parse_timestamps(mem, offset)
    assert offset == 0x2000

    level_table = {}
    for location in locations:
        try:
            level = parse_location(mem, location)
        except CountZeroException:
            continue
        x, z = level.x_pos, level.z_pos
        level_table[(x, z)] = level
        #with open(f"blocks__{x:02x}_{z:02x}.data", "wb") as f:
        #    f.write(level.blocks)

    with open(data_path + ".idx", "wb") as f:
        for index in devoxelize_region(level_table):
            f.write(struct.pack("<I", index))

    with open(data_path + ".vtx", "wb") as f:
        for vertex in linearized_vertex_buffer():
            vertex = [*vertex[0], *vertex[1], *vertex[2], vertex[3]]#, vertex[3]]
            f.write(struct.pack("<fffffffff", *vertex))

        #for chunk_x, chunk_z, block_index, block_id in devoxelize_region(level_table):
        #    #print(chunk_x, chunk_z, block_id)
        #    counts[block_id] += 1
        #    f.write(struct.pack("<bbBb", chunk_x, chunk_z, block_id, 0))
        #    f.write(struct.pack("<i", block_index))

mcr_path = sys.argv[1]
data_path = sys.argv[2]

main(mcr_path, data_path)
