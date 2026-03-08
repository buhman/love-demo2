from dataclasses import dataclass
import struct
import zlib

# https://minecraft.fandom.com/wiki/Region_file_format
# https://minecraft.wiki/w/NBT_format#Binary_format
# https://minecraft.wiki/w/Chunk_format/McRegion

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

def _xyz_from_block_index(block_index):
    assert block_index >= 0 and block_index < (128 * 16 * 16)
    x = block_index // (128 * 16)
    y = block_index % 128
    z = (block_index // 128) % 16
    return x, y, z

def _block_index_from_xyz(x, y, z):
    assert x >= 0 and x < 16
    assert y >= 0 and y < 128
    assert z >= 0 and z < 16
    return int(y + z * 128 + x * 128 * 16)

xyz_to_block_index = {}
block_index_to_xyz = {}

for i in range(128 * 16 * 16):
    xyz = _xyz_from_block_index(i)
    assert _block_index_from_xyz(*xyz) == i
    xyz_to_block_index[xyz] = i
    block_index_to_xyz[i] = xyz

def xyz_from_block_index(block_index):
    return block_index_to_xyz[block_index]

def block_index_from_xyz(x, y, z):
    return xyz_to_block_index[(x, y, z)]
