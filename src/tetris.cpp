#include <iostream>
#include <time.h>
#include "../include/tetris.h"

// int main() {
//     Tetris game(20, 10, 1);
//     action a;
//     int N = 100;
//     a.move = 1;
//     a.rot = 0;
//     for (int i=0; i<N; i++)
//         disp_matrix(game.get_state(a), game.r, game.c);
//     return 0;
// }
namespace tetris{
    Tetris::Tetris(int R, int C, int FR) {
        r = R;
        c = C;
        fall_rate = FR;
        gs = empty_game_state(r, c);
        active_block = init_block();
        i = 0;
        time_t t;
        srand( (unsigned) time(&t));
    }

    int* Tetris::get_state(action a) {
        game_step(a.rot, a.move, i);
        i++;
        return gs->display;
    }
}