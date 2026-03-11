import sys
import struct

paths = sys.argv[1:]

def main(path):
    with open(path, 'rb') as f:
        buf = memoryview(f.read())

    for i in range(len(buf) // 8):
        global_index, = struct.unpack("<i", buf[i*8:i*8+4])
        print(global_index)

for path in paths:
    main(path)
