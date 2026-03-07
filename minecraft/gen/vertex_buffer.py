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

def build_configuration_index_buffers(f, faces_by_normal):
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

def main():
    vertex_buffer = []
    index_buffer = []
    index_lookup = {}

    cube_state = obj.parse_obj_from_filename("cube.obj")

    obj_state.append_triangles(cube_state, vertex_buffer, index_buffer, index_lookup)
    cube_faces_by_normal = obj_state.build_faces_by_normal(vertex_buffer, index_buffer)

    tallgrass_index_start = len(index_buffer)
    tallgrass_state = obj.parse_obj_from_filename("tallgrass.obj")
    obj_state.append_triangles(tallgrass_state, vertex_buffer, index_buffer, index_lookup)
    tallgrass_index_count = len(index_buffer) - tallgrass_index_start
    print(tallgrass_index_start, tallgrass_index_count)

    with open("../configuration.idx", "wb") as f:
        build_configuration_index_buffers(f, cube_faces_by_normal)
        write_indices(f, index_buffer, tallgrass_index_start, tallgrass_index_count)

    with open("../per_vertex.vtx", "wb") as f:
        build_vertex_buffer(f, vertex_buffer)

if __name__ == "__main__":
    main()
