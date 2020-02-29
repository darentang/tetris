# distutils: language = c++

cdef extern from "tetris.cpp":
    pass

cdef extern from "tetris_core.c":
    pass


cdef extern from "../include/tetris_core.h":
    ctypedef int game_state
    ctypedef int offset
    ctypedef int block
    ctypedef struct action:
        int move
        int rot

cdef extern from "../include/tetris.h" namespace "tetris":
    cdef cppclass Tetris:
        int fall_rate
        game_state *gs
        block *active_block
        int i, r, c
        Tetris(int, int, int) except +
        Tetris() except +
        int* get_state(action) except +

