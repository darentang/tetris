"# distutils: language = c"

cdef extern from "../src/tetris_core.c":
    ctypedef struct game_state:
        pass
    ctypedef struct block:
        pass
    ctypedef struct offset:
        pass

    void step(game_state* gs,
              int r, 
              int c, 
              block* block,
              int rot,
              int dir,
              int mode)
    void get_random_block(block* block)
    block* init_block()
    game_state* empty_game_state(int r, int c)

cdef class Block:
    cdef block* b

    def __init__(self):
        self.b = init_block()

    @property
    def name(self):
        print(*(self.b).block_name)