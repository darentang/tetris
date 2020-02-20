#ifndef TETRIS_CORE
#define TETRIS_CORE
#include "../include/blocks.h"

void step(game_state* gs,
          int r, 
          int c, 
          struct block* block,
          int rot,
          int dir,
          int mode);

void get_random_block(struct block* block);

#endif