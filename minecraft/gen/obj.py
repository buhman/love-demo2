from dataclasses import dataclass

def ignore(state, line):
    pass

def normalize_float(s):
    f = float(s)
    if f == -0.0:
        return 0.0
    return f

def parse_float_components(s, length):
    components = s.split()
    assert len(components) == length
    return tuple(map(normalize_float, components))

def parse_position(state, line):
    position = parse_float_components(line, 3)
    state.position.append(position)

def parse_normal(state, line):
    normal = parse_float_components(line, 3)
    state.normal.append(normal)

def parse_texture(state, line):
    texture = parse_float_components(line, 2)
    state.texture.append(texture)

def parse_ptn(s):
    ptn = tuple(int(i) - 1 for i in s.split("/"))
    assert all(c >= 0 for c in ptn), ptn
    assert len(ptn) == 3, ptn
    return ptn

def parse_triangle(state, line):
    indices = line.split()
    assert len(indices) == 3, line
    triangle = tuple(map(parse_ptn, indices))
    state.triangle.append(triangle)

prefixes = [
    ("#", ignore),
    ("o ", ignore),
    ("s ", ignore),
    ("v ", parse_position),
    ("vn ", parse_normal),
    ("vt ", parse_texture),
    ("f ", parse_triangle),
]

@dataclass
class ObjState:
    position: list
    normal: list
    texture: list
    triangle: list

    def __init__(self):
        self.position = []
        self.normal = []
        self.texture = []
        self.triangle = []

def parse_obj(s):
    state = ObjState()
    lines = s.strip().split("\n")
    for line in lines:
        for prefix, func in prefixes:
            if line.startswith(prefix):
                line = line.removeprefix(prefix)
                func(state, line)
                break
        else:
            assert False, line
    return state

def parse_obj_from_filename(filename):
    with open(filename, "r") as f:
        buf = f.read()
    return parse_obj(buf)
