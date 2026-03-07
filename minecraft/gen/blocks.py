import struct

unk = 185

lookup = {
    k: v for k, v, _ in mapping
}

with open("block_id_to_texture_id.data", "wb") as f:
    for i in range(256):
        value = lookup.get(i, unk)
        f.write(struct.pack("<i", value))
        print(str(value).rjust(3), end=', ')
        if i % 16 == 15:
            print()
