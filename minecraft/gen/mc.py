import sys
import struct
from pprint import pprint
from itertools import chain
from collections import defaultdict
import functools
import os

import mcregion
import vec3
import vertex_buffer
import data
import block_ids

def wrap_n(nc, chunk_c):
    if nc < 0:
        nc = 15
        chunk_c = chunk_c - 1
    if nc > 15:
        nc = 0
        chunk_c = chunk_c + 1
    return nc, chunk_c

def decode_block_data(level_table, chunk_x, chunk_z, block_index):
    block_data = level_table[(chunk_x, chunk_z)].data[block_index // 2]
    #block_data = (block_data >> (1 - (block_index % 2)) * 4) & 0xf
    block_data = (block_data >> (block_index % 2) * 4) & 0xf
    return block_data

def neighbor_exists(level_table, chunk_x, chunk_z, nx, ny, nz):
    if ny > 127 or ny < 0:
        return False
    nx, n_chunk_x = wrap_n(nx, chunk_x)
    nz, n_chunk_z = wrap_n(nz, chunk_z)
    assert nx <= 15 and nx >= 0
    assert nz <= 15 and nz >= 0
    key = (n_chunk_x, n_chunk_z)
    if key not in level_table:
        return True
    n_block_index = mcregion.block_index_from_xyz(nx, ny, nz)
    n_block_id = level_table[key].blocks[n_block_index]
    n_block_data = decode_block_data(level_table, chunk_x, chunk_z, n_block_index)
    return block_ids.is_neighbor_block(n_block_id, n_block_data)

def outside_crop(position, crop):
    return (
        position[0] < crop[0][0] or
        position[2] < crop[0][1] or
        position[0] > crop[1][0] or
        position[2] > crop[1][1]
    )

def block_neighbors(level_table, chunk_x, chunk_z, block_index, crop):
    block_id = level_table[(chunk_x, chunk_z)].blocks[block_index]
    if block_id == data.BlockID.AIR or block_id == data.BlockID.BEDROCK:
        return

    block_data = decode_block_data(level_table, chunk_x, chunk_z, block_index)

    xyz = mcregion.xyz_from_block_index(block_index)
    center_position = vec3.add(xyz, (chunk_x * 16, 0, chunk_z * 16))
    if outside_crop(center_position, crop):
        return # block is cropped

    if not block_ids.is_cube_block(block_id, block_data):
        yield center_position, block_id, block_data, None
        return

    def find_non_neighbors():
        for i, normal in enumerate(vertex_buffer.normals):
            neighbor = vec3.add(normal, xyz)
            if not neighbor_exists(level_table, chunk_x, chunk_z, *neighbor):
                yield i

    normal_indices = list(find_non_neighbors())
    if normal_indices:
        yield center_position, block_id, block_data, normal_indices

def devoxelize_region(level_table, level_table_keys, crop):
    for chunk_x, chunk_z in level_table_keys:
        for block_index in range(128 * 16 * 16):
            yield from block_neighbors(level_table, chunk_x, chunk_z, block_index, crop)

def build_level_table(level_table, mem, locations):
    for location in locations:
        try:
            level = mcregion.parse_location(mem, location)
        except mcregion.CountZeroException:
            continue
        x, z = level.x_pos, level.z_pos
        level_table[(x, z)] = level
    return level_table

def normal_indices_as_block_configuration(normal_indices):
    acc = 0
    for i in normal_indices:
        acc |= (1 << i)
    return acc

def build_block_configuration_table():
    for i in range(64):
        indices = []
        for j in range(6):
            if ((i >> j) & 1) != 0:
                indices.extend(vertex_buffer.faces_by_normal[vertex_buffer.normals[j]])
        yield indices

def pack_instance_data(position, block_id, block_data, texture_id):
    special = block_ids.get_special(block_id, block_data)

    packed = struct.pack("<hhhhhhhh",
                         position[0], position[1], position[2], 0,
                         block_id, block_data, texture_id, special)
    return packed

def pack_light_data(position, block_id, block_data):
    packed = struct.pack("<ffff", position[0], position[1], position[2], block_data)
    return packed

def build_block_instances(blocks):
    by_configuration = defaultdict(list)

    non_cube_blocks = defaultdict(list)

    light_sources = []

    for position, block_id, block_data, normal_indices in blocks:
        if block_id == 44:
            print("bd", block_data)
        if block_ids.is_light_source(block_id, block_data):
            light_sources.append((position, block_id, block_data))
        if not block_ids.is_cube_block(block_id, block_data):
            if block_id == 44:
                print(block_id)
            custom_mesh_index = block_ids.get_custom_mesh_index(block_id, block_data)
            non_cube_blocks[custom_mesh_index].append((position, block_id, block_data))
            continue
        configuration = normal_indices_as_block_configuration(normal_indices)
        by_configuration[configuration].append((position, block_id, block_data))

    offset = 0
    configuration_instance_count_offset = []
    with open(f"{data_path}.instance.vtx", "wb") as f:
        ######################################################################
        # cubes
        ######################################################################
        for configuration in range(64):
            if configuration not in by_configuration:
                configuration_instance_count_offset.append((0, 0))
                continue
            _blocks = by_configuration[configuration]
            configuration_instance_count_offset.append((len(_blocks), offset))
            for position, block_id, block_data in _blocks:
                texture_id = block_ids.get_texture_id(block_id, block_data)
                packed = pack_instance_data(position, block_id, block_data, texture_id)
                f.write(packed)
                offset += len(packed)

        ######################################################################
        # non-cubes
        ######################################################################
        for custom_block_ix in range(len(block_ids.sorted_custom_mesh)):
            nc_offset = offset
            nc_instance_count = 0
            for position, block_id, block_data in non_cube_blocks[custom_block_ix]:
                texture_id = block_ids.get_texture_id(block_id, block_data)
                packed = pack_instance_data(position, block_id, block_data, texture_id)
                f.write(packed)
                assert len(packed) == 16
                offset += len(packed)
                nc_instance_count += 1
            configuration_instance_count_offset.append((nc_instance_count, nc_offset))

    with open(f"{data_path}.instance.cfg", "wb") as f:
        for instance_count, offset in configuration_instance_count_offset:
            #print(instance_count, offset)
            f.write(struct.pack("<ii", instance_count, offset))

    with open(f"{data_path}.lights.vtx", "wb") as f:
        for position, block_id, block_data in light_sources:
            packed = pack_light_data(position, block_id, block_data)
            f.write(packed)

def level_table_from_path(level_table, path):
    with open(path, "rb") as f:
        buf = f.read()
    mem = memoryview(buf)

    offset = 0
    offset, locations = mcregion.parse_locations(mem, offset)
    offset, timestamps = mcregion.parse_timestamps(mem, offset)
    assert offset == 0x2000

    build_level_table(level_table, mem, locations)

g_stride = 512 * 2
def from_global_index(i):
    x, y, z = i % g_stride, i // (g_stride * g_stride), (i // g_stride) % g_stride
    if x >= 512:
        x = -x + 511
    if z >= 512:
        z = -z + 511
    assert x < 512 and z < 512
    return x, y, z

def to_global_index(x,y,z):
    assert x >= -512 and x < 512, (x, y, z)
    assert y >= 0 and y < 128, (x, y, z)
    assert z >= -512 and z < 512, (x, y, z)
    original_coordinate = (x, y, z)
    if x < 0:
        x = -(x - 511)
    if z < 0:
        z = -(z - 511)
    assert z >= 0 and x >= 0
    value = x + z * g_stride + y * g_stride * g_stride
    assert from_global_index(value) == original_coordinate, (original_coordinate, value)
    return value

def dump_blocks(blocks):
    with open(f"{data_path}.dump", "wb") as f:
        for block in blocks:
            center_position, block_id, block_data, normal_indices = block
            global_index = to_global_index(*center_position)
            buf = struct.pack("<iBBBB", global_index, block_id, block_data, 0, 0)
            assert(len(buf) == 8)
            f.write(buf)

def main2(level_table, level_table_keys, crop):
    print("crop", crop)
    blocks = devoxelize_region(level_table, level_table_keys, crop)
    blocks = list(blocks)
    dump_blocks(blocks)
    build_block_instances(blocks)
    print("blocks_length:", len(blocks))

def parse_all_paths(path):
    with open(path, 'r') as f:
        buf = f.read()
    return set(l.strip() for l in buf.split('\n') if l.strip())

def parse_crop(crop):
    min_xz, max_xz = crop.strip().split(":")
    min_xz = tuple(int(c) for c in min_xz.split(","))
    max_xz = tuple(int(c) for c in max_xz.split(","))
    assert min_xz[0] < max_xz[0], crop
    assert min_xz[1] < max_xz[1], crop
    return min_xz, max_xz

def main(mcr_path, data_path, all_paths_path, crop):
    all_paths = parse_all_paths(all_paths_path)
    assert mcr_path in all_paths
    level_table = {}
    level_table_from_path(level_table, mcr_path)
    level_table_keys = list(level_table.keys())
    for path in all_paths:
        if path == mcr_path:
            continue
        level_table_from_path(level_table, path)
    main2(level_table, level_table_keys, parse_crop(crop))

mcr_path = sys.argv[1]
data_path = sys.argv[2]
all_paths_path = sys.argv[3]
crop = sys.argv[4]
main(mcr_path, data_path, all_paths_path, crop)
