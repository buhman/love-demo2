import struct
import vec3
import obj
import obj_state
import sys

normals = [
    (-1.0, 0.0, 0.0),
    (0.0, -1.0, 0.0),
    (0.0, 0.0, -1.0),
    (0.0, 0.0, 1.0),
    (0.0, 1.0, 0.0),
    (1.0, 0.0, 0.0),
]

def build_configuration_index_buffers(f, faces_by_normal, index_buffer):
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
                f.write(struct.pack("<B", index))
                index_buffer.append(index)
                offset += 1

    for i, offset in enumerate(configuration_offsets):
        print(str(offset).rjust(4), end=", ")
        if i % 8 == 7:
            print()

def build_vertex_buffer(f, vertex_buffer):
    for position, normal, texture in vertex_buffer:
        position = vec3.mul(position, 0.5)
        f.write(struct.pack("<eeeeeeee", *position, *normal, *texture))

def write_indices(f, index_buffer, start, count):
    for i in range(count):
        f.write(struct.pack("<B", index_buffer[start + i]))

def write_custom_obj(f, vertex_buffer, index_buffer, index_lookup, path):
    index_start = len(index_buffer)
    state = obj.parse_obj_from_filename(path)
    obj_state.append_triangles(state, vertex_buffer, index_buffer, index_lookup)
    index_count = len(index_buffer) - index_start
    write_indices(f, index_buffer, index_start, index_count)
    print(f"{index_start}, {index_count}, // {path}")

def main():
    cube_index_buffer = []
    cube_index_lookup = {}

    vertex_buffer = []
    index_buffer = []
    index_lookup = {}

    cube_state = obj.parse_obj_from_filename("cube.obj")

    obj_state.append_triangles(cube_state, vertex_buffer, cube_index_buffer, cube_index_lookup)
    cube_faces_by_normal = obj_state.build_faces_by_normal(vertex_buffer, cube_index_buffer)

    with open("../configuration.idx", "wb") as f:
        build_configuration_index_buffers(f, cube_faces_by_normal, index_buffer)
        index_lookup = {}
        write_custom_obj(f, vertex_buffer, index_buffer, index_lookup, "tallgrass.obj")
        index_lookup = {}
        write_custom_obj(f, vertex_buffer, index_buffer, index_lookup, "fence.obj")
        index_lookup = {}
        write_custom_obj(f, vertex_buffer, index_buffer, index_lookup, "torch.obj")
        index_lookup = {}
        write_custom_obj(f, vertex_buffer, index_buffer, index_lookup, "wheat.obj")

    with open("../per_vertex.vtx", "wb") as f:
        build_vertex_buffer(f, vertex_buffer)

if __name__ == "__main__":
    main()
