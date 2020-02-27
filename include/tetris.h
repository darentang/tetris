#ifndef TETRIS
#define TETRIS

#include<Python/Python.h>

extern "C" {
    #include "../include/tetris_core.h"
}

typedef struct Action {
    int rot;
    int move;
} action;

class Tetris {
    int fall_rate;
    game_state *gs;
    block *active_block;
    int i;

    public:
        int r, c;
        Tetris(int R, int C, int FR) {
            r = R;
            c = C;
            fall_rate = FR;
            gs = empty_game_state(r, c);
            active_block = init_block();
            i = 0;
        }
        int* get_state(action a) {
            game_step(a.rot, a.move, i);
            i++;
            return gs->display;
        }

    private:
        void game_step(int rot, int move, int i) {
            // falling
            if (i % fall_rate == 0){
                step(gs, r, c, active_block, 0, 0, 1);
            }
            // moving
            step(gs, r, c, active_block, rot, move, 0);
        }
};

#endif