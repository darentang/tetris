#ifndef TETRIS_H
#define TETRIS_H

extern "C" {
    #include "../include/tetris_core.h"
}

namespace tetris {
    class Tetris {
        public:
            int fall_rate;
            game_state *gs;
            block *active_block;
            int i;
            int r, c;
            Tetris(int R, int C, int FR);
            Tetris(){};
            int* get_state(action a);
        private:
            void game_step(int rot, int move, int i) {
                // moving
                step(gs, r, c, active_block, rot, move, 0);
                // falling
                if (i % fall_rate == 0){
                    step(gs, r, c, active_block, 0, 0, 1);
                }
            }
    };
}
#endif