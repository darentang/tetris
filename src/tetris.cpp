#include <iostream>
#include "../include/tetris.hpp"

int main() {
    Tetris game(20, 10, 1);
    action a;
    int N = 100;
    a.move = 1;
    a.rot = 0;
    for (int i=0; i<N; i++)
        disp_matrix(game.get_state(a), game.r, game.c);
    return 0;
}