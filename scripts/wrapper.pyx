"# distutils: language = c"

cdef extern from "../src/tetris_core.h":
    ctypedef struct game_state:
        pass
    struct block
    struct offset

    void step(game_state* gs,
              int r, 
              int c, 
              struct block* block,
              int rot,
              int dir,
              int mode)
    void get_random_block(struct block* block)
    struct block* init_block(void)
    game_state* empty_game_state(int r, int c)

