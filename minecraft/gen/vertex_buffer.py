import vec3

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
        position = vec3.add(vec3.mul(position, 0.5), center_position)
        vertex = (position, normal, texture, block_id)
        new_index = add_vertex(vertex)
        yield new_index

def linearized_vertex_buffer():
    for vertex, i in sorted(vertex_buffer.items(), key=lambda kv: kv[1]):
        yield vertex

#with open(data_path + ".vtx", "wb") as f:
#    for vertex in linearized_vertex_buffer():
#        vertex = [*vertex[0], *vertex[1], *vertex[2], vertex[3]]#, vertex[3]]
#        f.write(struct.pack("<fffffffff", *vertex))
