import struct
import data
import sys

unk = 253

with open(sys.argv[1], "wb") as f:
    for i in range(256):
        if i in data.tiles_by_id:
            value = data.tiles_by_id[i].texture
        else:
            value = unk
        f.write(struct.pack("<i", value))
