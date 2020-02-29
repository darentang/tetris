#ifndef TETRIS_CORE
#define TETRIS_CORE

typedef struct GameState{
    int* display;
    int* active;
    int* inactive;
} game_state;

typedef struct Offset{
    int i, j;
} offset;

typedef struct Block{
    char block_name;
    offset *offset;
    int rot;
    int *block_coor;
} block;

typedef struct Action {
    int rot;
    int move;
} action;


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

void disp_matrix(int* arr, int r, int c);

void foo();

#endif
