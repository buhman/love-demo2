import sys
import struct
from pprint import pprint
from itertools import chain
from collections import defaultdict

import mcregion
import vec3
import vertex_buffer

def wrap_n(nc, chunk_c):
    if nc < 0:
        nc = 15
        chunk_c = chunk_c - 1
    if nc > 15:
        nc = 0
        chunk_c = chunk_c + 1
    return nc, chunk_c

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
        n_block_index = mcregion.block_index_from_xyz(nx, ny, nz)
        key = (n_chunk_x, n_chunk_z)
        if key not in level_table:
            return True
        n_block_id = level_table[key].blocks[n_block_index]
        return n_block_id != 0

    x, y, z = mcregion.xyz_from_block_index(block_index)

    center_position = vec3.add((x, y, z), (chunk_x * 16, 0, chunk_z * 16))

    def find_non_neighbors():
        for i, normal in enumerate(vertex_buffer.normals):
            neighbor = vec3.add(normal, (x, y, z))
            if not neighbor_exists(*neighbor):
                yield i

    normal_indices = list(find_non_neighbors())
    if normal_indices:
        yield center_position, block_id, normal_indices

def devoxelize_region(level_table):
    for chunk_x, chunk_z in level_table.keys():
        for block_index in range(128 * 16 * 16):
            yield from block_neighbors(level_table, chunk_x, chunk_z, block_index)

def build_level_table(mem, locations):
    level_table = {}
    for location in locations:
        try:
            level = mcregion.parse_location(mem, location)
        except CountZeroException:
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

def build_block_instances(blocks):
    by_configuration = defaultdict(list)

    for position, block_id, normal_indices in blocks:
        configuration = normal_indices_as_block_configuration(normal_indices)
        #print(position, block_id, block_configuration)
        by_configuration[configuration].append((position, block_id))

    offset = 0
    configuration_instance_count_offset = []
    with open(f"{data_path}.instance.vtx", "wb") as f:
        for configuration in range(64):
            if configuration not in by_configuration:
                configuration_instance_count_offset.append((0, 0))
                continue
            blocks = by_configuration[configuration]
            configuration_instance_count_offset.append((len(blocks), offset))
            for position, block_id in blocks:
                packed = struct.pack("<hhhBB",
                                     position[0], position[1], position[2],
                                     block_id,
                                     0)
                f.write(packed)
                offset += len(packed)

    with open(f"{data_path}.instance.cfg", "wb") as f:
        for instance_count, offset in configuration_instance_count_offset:
            print(instance_count, offset)
            f.write(struct.pack("<ii", instance_count, offset))

def main(mcr_path, data_path):
    with open(mcr_path, "rb") as f:
        buf = f.read()
    mem = memoryview(buf)

    offset = 0
    offset, locations = mcregion.parse_locations(mem, offset)
    offset, timestamps = mcregion.parse_timestamps(mem, offset)
    assert offset == 0x2000

    level_table = build_level_table(mem, locations)
    blocks = devoxelize_region(level_table)
    build_block_instances(blocks)

    #pprint(list(build_block_configuration_table()))

mcr_path = sys.argv[1]
data_path = sys.argv[2]

main(mcr_path, data_path)
