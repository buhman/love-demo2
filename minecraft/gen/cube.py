positions = [
    (1.0, 1.0, -1.0),
    (1.0, -1.0, -1.0),
    (1.0, 1.0, 1.0),
    (1.0, -1.0, 1.0),
    (-1.0, 1.0, -1.0),
    (-1.0, -1.0, -1.0),
    (-1.0, 1.0, 1.0),
    (-1.0, -1.0, 1.0)
]

normals = [
  (0.0, 1.0, 0.0),
  (0.0, 0.0, 1.0),
  (-1.0, 0.0, 0.0),
  (0.0, -1.0, 0.0),
  (1.0, 0.0, 0.0),
  (0.0, 0.0, -1.0),
]

textures = [
  (1.0, 0.0),
  (0.0, 1.0),
  (0.0, 0.0),
  (1.0, 1.0),
  (0.0, 0.0),
  (1.0, 0.0),
]

indices = [
  [
    [4, 0, 0],
    [2, 1, 0],
    [0, 2, 0],
  ],
  [
    [2, 3, 1],
    [7, 4, 1],
    [3, 5, 1],
  ],
  [
    [6, 3, 2],
    [5, 4, 2],
    [7, 5, 2],
  ],
  [
    [1, 0, 3],
    [7, 1, 3],
    [5, 2, 3],
  ],
  [
    [0, 3, 4],
    [3, 4, 4],
    [1, 5, 4],
  ],
  [
    [4, 3, 5],
    [1, 4, 5],
    [5, 5, 5],
  ],
  [
    [4, 0, 0],
    [6, 3, 0],
    [2, 1, 0],
  ],
  [
    [2, 3, 1],
    [6, 1, 1],
    [7, 4, 1],
  ],
  [
    [6, 3, 2],
    [4, 1, 2],
    [5, 4, 2],
  ],
  [
    [1, 0, 3],
    [3, 3, 3],
    [7, 1, 3],
  ],
  [
    [0, 3, 4],
    [2, 1, 4],
    [3, 4, 4],
  ],
  [
    [4, 3, 5],
    [0, 1, 5],
    [1, 4, 5],
  ],
]

vertex_buffer = []
index_buffer = []
index_lookup = {}

for triangle in indices:
    for p_ix, t_ix, n_ix in triangle:
        key = (p_ix, n_ix, t_ix)
        if key not in index_lookup:
            position = positions[p_ix]
            normal = normals[n_ix]
            texture = textures[t_ix]
            index = len(vertex_buffer)
            index_lookup[key] = index
            vertex_buffer.append((tuple(position),
                                  tuple(normal),
                                  tuple(texture)))

        index_buffer.append(index_lookup[key])

def gen():
    for position, normal, texture in vertex_buffer:
        p = ", ".join(map(str, map(float, position)))
        n = ", ".join(map(str, map(float, normal)))
        t = ", ".join(map(str, map(float, texture)))
        print(f"vertex_t(vec3({p}), vec3({n}), vec2({t})),")

    for i in range(len(index_buffer) // 3):
        tri = ", ".join(str(index_buffer[i * 3 + n]) for n in range(3))
        print(f"{tri},")

from collections import defaultdict
by_normal = defaultdict(list)
for i in range(len(index_buffer) // 3):
    tri = [index_buffer[i * 3 + n] for n in range(3)]
    s = set(vertex_buffer[j][1] for j in tri)
    assert len(s) == 1
    normal, = iter(s)
    by_normal[normal].append(tri)

from pprint import pprint
pprint(dict(by_normal))
pprint(vertex_buffer)
