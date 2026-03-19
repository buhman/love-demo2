import csv
from dataclasses import dataclass
import data

@dataclass
class Decl:
    name: str
    block_id: int
    data: int
    linear_texture_index: str
    custom_mesh: str
    properties: set[str]

def decls():
    with open("block_ids.csv", "r") as f:
        reader = csv.reader(f)
        rows = list(reader)

    header = ('name', 'block id', 'data', 'linear texture index', 'custom mesh', 'properties')
    assert tuple(rows[0][:len(header)]) == header, rows[0]
    data_rows = rows[1:]
    for name, block_id, data, texture_index, custom_mesh, properties, *_ in data_rows:
        block_id = int(block_id)
        texture_index = (int(texture_index) - 1) if texture_index.strip() != '' else 62
        custom_mesh = custom_mesh if custom_mesh.strip() != '' else 'cube'
        properties = set(properties.split(','))
        if ',' in data:
            for d in data.split(","):
                yield Decl(name, block_id, int(d), texture_index, custom_mesh, properties)
        else:
            data = int(data) if data.strip() != '' else 0
            yield Decl(name, block_id, data, texture_index, custom_mesh, properties)

def key_block_id_data(decl):
    return decl.block_id, decl.data

sorted_decls = list(sorted(decls(), key=key_block_id_data))
by_id_data = {
    (decl.block_id, decl.data): decl
    for decl in sorted_decls
}

default_decl = Decl(
    name = "_undefined",
    block_id = 999,
    data = 111,
    linear_texture_index = 62,
    custom_mesh = "cube",
    properties = set(),
)

def is_neighbor_block(block_id, block_data):
    if block_id == data.BlockID.AIR:
        return False
    decl = by_id_data.get((block_id, block_data), default_decl)
    return decl.custom_mesh == 'cube'

def is_light_source(block_id, block_data):
    decl = by_id_data.get((block_id, block_data), default_decl)
    return 'emits_light' in decl.properties

def is_cube_block(block_id, block_data):
    decl = by_id_data.get((block_id, block_data), default_decl)
    return decl.custom_mesh == 'cube'

sorted_custom_mesh = list(sorted(set(decl.custom_mesh for decl in sorted_decls if decl.custom_mesh != "cube")))
custom_mesh_index = {
    custom_mesh: index
    for index, custom_mesh in enumerate(sorted_custom_mesh)
}

def get_custom_mesh_index(block_id, block_data):
    decl = by_id_data.get((block_id, block_data), default_decl)
    return custom_mesh_index[decl.custom_mesh]

def get_texture_id(block_id, block_data):
    decl = by_id_data.get((block_id, block_data), default_decl)
    return decl.linear_texture_index

if __name__ == "__main__":
    print(sorted_custom_mesh)
