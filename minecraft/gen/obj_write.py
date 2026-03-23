import struct
import vec3
import obj
import obj_state

def write_vertex_buffer(f, vertex_buffer):
    for position, normal, texture in vertex_buffer:
        position = vec3.mul(position, 0.5)
        f.write(struct.pack("<eeeeeeee", *position, *normal, *texture))

def write_indices(f, index_format, index_buffer):
    for i in range(len(index_buffer)):
        f.write(struct.pack(index_format, index_buffer[i]))

def write_obj(vertex_buffer, index_buffer, index_lookup, path):
    index_start = len(index_buffer)
    state = obj.parse_obj_from_filename(path)
    obj_state.append_triangles(state, vertex_buffer, index_buffer, index_lookup)
    index_count = len(index_buffer) - index_start
    print(f"{{{index_start}, {index_count}}}, // {path}")
