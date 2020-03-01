# distutils: language = c++

from Tetris cimport Tetris, action
import numpy as np

cdef class PyTetris:

    cdef Tetris c_tetris

    cdef action c_action

    def __cinit__(self, int R, int C, int FR):
        self.c_tetris = Tetris(R, C, FR)
        self.c_action.move = 0
        self.c_action.rot = 0

    def get_state(self, int move=0, int rot=0):
        self.c_action.move = move
        self.c_action.rot = rot
        cdef int[::1] view = <int[:3 * self.c_tetris.r * self.c_tetris.c]> self.c_tetris.get_state(self.c_action)
        return np.asarray(view).reshape(3, self.r, self.c)

    @property
    def r(self):
        return self.c_tetris.r

    @property
    def c(self):
        return self.c_tetris.c

    @property
    def fall_rate(self):
        return self.c_tetris.fall_rate

    @fall_rate.setter
    def fall_rate(self, fr):
        self.c_tetris.fall_rate = fr