import struct
from collections import defaultdict
import sys

import data

files = sys.argv[1:]

by_block_id = defaultdict(list)
no_tile = defaultdict(list)

block_ids = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    45,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    93,
    94,
    95,
    96,
    97,
    98,
    99,
    100,
    101,
    102,
    103,
    104,
    105,
    106,
    107,
    108,
    109,
    110,
    111,
    112,
    113,
    114,
    115,
}

for filename in files:
    with open(filename, 'rb') as f:
        buf = f.read()
    for i in range(len(buf) // 8):
        x, y, z, block_id, block_data = struct.unpack("<hhhBB", buf[i*8:i*8+8])
        if block_id == 35:
            print(x, y, z, block_data)

        if block_id not in block_ids and block_id not in data.tiles_by_id:
            by_block_id[block_id].append((x, y, z, block_data))
        elif block_id not in data.tiles_by_id:
            no_tile[block_id].append((x, y, z, block_data))

print("no block id:")
for key in sorted(by_block_id.keys()):
    print(" ", key, len(by_block_id[key]), by_block_id[key][0])

print("no tile:")
for key in sorted(no_tile.keys()):
    print(" ", key, len(no_tile[key]), no_tile[key][0])
