import struct
import vec3
import obj
import obj_state
import obj_write
import sys

import block_ids

normals = [
    (-1.0, 0.0, 0.0),
    (0.0, -1.0, 0.0),
    (0.0, 0.0, -1.0),
    (0.0, 0.0, 1.0),
    (0.0, 1.0, 0.0),
    (1.0, 0.0, 0.0),
]

def build_configuration_index_buffers(faces_by_normal, index_buffer):
    assert(set(normals) == set(faces_by_normal.keys()))

    offset = 0
    configuration_offsets = []
    for configuration in range(64):
        configuration_offsets.append(offset)
        for i in range(6):
            if (configuration & (1 << i)) == 0:
                continue
            normal = normals[i]
            indices = faces_by_normal[normal]
            for index in indices:
                #f.write(struct.pack("<B", index))
                index_buffer.append(index)
                offset += 1

    for i, offset in enumerate(configuration_offsets):
        print(str(offset).rjust(4), end=", ")
        if i % 8 == 7:
            print()

def main():
    vertex_buffer = []
    index_buffer = []
    index_lookup = {}

    cube_state = obj.parse_obj_from_filename("cube.obj")

    tmp_index_buffer = [] # discarded
    obj_state.append_triangles(cube_state, vertex_buffer, tmp_index_buffer, index_lookup)
    cube_faces_by_normal = obj_state.build_faces_by_normal(vertex_buffer, tmp_index_buffer)

    build_configuration_index_buffers(cube_faces_by_normal, index_buffer)
    # check mc.py `custom_blocks` for model order

    mesh_order = block_ids.sorted_custom_mesh
    for mesh_name in mesh_order:
        obj_write.write_obj(vertex_buffer, index_buffer, index_lookup, f"{mesh_name}.obj")

    with open("../configuration.idx", "wb") as f:
        obj_write.write_indices(f, "<H", index_buffer)

    with open("../per_vertex.vtx", "wb") as f:
        obj_write.write_vertex_buffer(f, vertex_buffer)

if __name__ == "__main__":
    main()
