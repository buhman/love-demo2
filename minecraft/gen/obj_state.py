from collections import defaultdict
import obj

def append_triangles(state, vertex_buffer, index_buffer, index_lookup):
    for triangle in state.triangle:
        for p_ix, t_ix, n_ix in triangle:
            position = state.position[p_ix]
            normal = state.normal[n_ix]
            texture = state.texture[t_ix]
            key = (position, normal, texture)
            if key not in index_lookup:
                index = len(vertex_buffer)
                index_lookup[key] = index
                vertex_buffer.append((position, normal, texture))
            index_buffer.append(index_lookup[key])

def build_faces_by_normal(vertex_buffer, index_buffer):
    by_normal = defaultdict(list)
    for i in range(len(index_buffer) // 3):
        tri = [index_buffer[i * 3 + n] for n in range(3)]
        s = set(vertex_buffer[j][1] for j in tri)
        assert len(s) == 1, s
        normal, = iter(s)
        by_normal[normal].extend(tri)
    return by_normal
