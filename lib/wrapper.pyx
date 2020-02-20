cdef extern from "../src/tetris_core.h":
    void step(int* active, 
            int* inactive, 
            int* display, 
            int r, 
            int c, 
            struct block *block,
            int rot,
            int dir,
            int mode)

    void get_random_block(struct block* block)

def py_hello(name: bytes) -> None:
    hello(name)