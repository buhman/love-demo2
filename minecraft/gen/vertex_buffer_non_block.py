import obj_write

def main():
    vertex_buffer = []
    index_buffer = []
    index_lookup = {}

    obj_write.write_obj(vertex_buffer, index_buffer, index_lookup, "icosphere.obj")

    with open("../non_block.idx", "wb") as f:
        obj_write.write_indices(f, "<H", index_buffer)

    with open("../non_block.vtx", "wb") as f:
        obj_write.write_vertex_buffer(f, vertex_buffer)

if __name__ == "__main__":
    main()
