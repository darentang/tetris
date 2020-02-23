#ifndef TETRIS_CORE
#define TETRIS_CORE
#include "blocks.h"

void step(game_state* gs,
          int r, 
          int c, 
          block* block,
          int rot,
          int dir,
          int mode);
void get_random_block(block* block);

block* init_block(void);
game_state* empty_game_state(int r, int c);

#endif