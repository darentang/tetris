#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../include/blocks.h"
#include "../include/tetris_core.h"

void delay(long miliseconds){ 
    
    miliseconds *= 1000;

    // Storing start time 
    clock_t start_time = clock();     

    // looping till required time is not achieved 
    while (clock() < start_time + miliseconds);
}

void disp_matrix(int *mat, int r, int c){
    for (int i=0; i<r; i++){
        printf("%02d|", i);
        for (int j=0; j<c; j++){
            printf("%3d", *(mat + i*c + j));
            // if (*(mat + i*c + j)){
            //     printf("#");
            // }else{
            //     printf(" ");
            // }
        }
        printf("|\n");
    }
    printf("\n");
}

int* zeros(int r, int c){
    int *arr = (int*)calloc(c * r, sizeof(int));
    return arr;
}

int* ones(int r, int c){
    int i, j;
    int *arr = (int*)malloc(c * r * sizeof(int));
    for (i=0; i<r; i++){
        for (j=0; j<c; j++){
            *(arr + i*c + j) = 1;
        }
    }
    return arr;
}

bool is_inrange(int x, int d){
    return (0 <= x && x < d);
}

void reset_zero(int *arr, int r, int c){
    for (int i = 0; i < r; i ++){
        for (int j = 0; j < c; j ++){
            *(arr + c * i + j) = 0;
        }
    }
}

void deepcopy(int* from, int* to, int n){
    for (int i = 0; i < n; i ++){
        *(to + i) = *(from + i);
    }
}

bool form_active_screen(int* arr, int* block, offset* o, int r, int c){
    int i, j;
    int temp_arr[r * c];
    reset_zero(&temp_arr[0], r, c);
    for (int k = 0; k < 16; k++){
        i = k % 4 + (o->i);
        j = (int)floor(k / 4) + (o->j);
        if (block[k]){
            if ((!is_inrange(i, r) || !is_inrange(j, c))){
                return false;
            }else{
                temp_arr[i*c + j] = block[k];
            }
        }
    }
    deepcopy(&temp_arr[0], arr, r * c);
    return true;
}

void merge(int* arr1, int* arr2, int* out_arr, int r, int c, char name){
    int col[3];
    switch(name){
        case 'I':
            col[0] = 0;
            col[1] = 255;
            col[2] = 255;
            break;
        case 'J':
            col[0] = 0;
            col[1] = 0;
            col[2] = 255;
            break;
        case 'L':
            col[0] = 256;
            col[1] = 165;
            col[2] = 0;
            break;
        case 'O':
            col[0] = 255;
            col[1] = 255;
            col[2] = 0;
            break;
        case 'S':
            col[0] = 0;
            col[1] = 255;
            col[2] = 0;
            break;
        case 'T':
            col[0] = 128;
            col[1] = 0;
            col[2] = 128;
            break;
        case 'Z':
            col[0] = 255;
            col[1] = 0;
            col[2] = 0;
            break;
        default:
            col[0] = 0;
            col[1] = 0;
            col[2] = 0;
    }
    for (int i = 0; i < r ; i ++){
        for (int j = 0; j < c; j++){
            for (int ch = 0; ch < 3; ch++){
                *(out_arr + ch * r * c + c * i + j) = *(arr2 + ch * r * c + c * i + j) + 
                col[ch] * *(arr1 + c * i + j);
                if (*(out_arr + ch * r * c + c * i + j) > 255){
                    *(out_arr + ch * r * c + c * i + j) = 255;
                }
            }                
        }
    }
}

bool check_collide(int* arr1, int* arr2, int r, int c){
    for (int i = 0; i < r ; i ++){
        for (int j = 0; j < c; j++){
            int sum = 0;
            for (int ch = 0; ch < 3; ch ++){
                sum += *(arr2 + ch * r * c + c * i + j);
            }
            if (*(arr1 + c * i + j) * sum != 0){
                return true;
            }
        }
    }
    return false;
}

void reset_offset(offset *o){
    o->i = 0;
    o->j = 3;
}

void get_random_block(block *block){
    int n = rand() % 7;
    block->block_name = stdblocks[n].name;
    block->block_coor = &stdblocks[n].pos[0][0];
    block->rot = 0;
    block->offset = (offset*) malloc(sizeof(offset));
    reset_offset(block->offset);
}

void fall(offset *o){
    o->i ++;
}

void move(offset *o, int direction){
    o->j += direction;
}

void step(game_state* gs, 
          int r, 
          int c, 
          block *block,
          int rot,
          int dir,
          int mode){
    

    offset *poffset;
    poffset = (offset*) malloc(sizeof(offset));

    bool valid = false;

    int* block_coor = block->block_coor + 16 * block->rot;

    int* desired_block_coor;

    // save previous state
    *poffset = *(block->offset);

    if (mode == 0){
        move(poffset, dir);
        desired_block_coor = block->block_coor + 16 * rot;
    } else if (mode == 1){
        // fall down one step
        fall(poffset);
        desired_block_coor = block_coor;
    }

    
    // Check out of bounds
    if (form_active_screen(gs->active, desired_block_coor, poffset, r, c)){
        // Check collisions with passive
        if (!check_collide(gs->active, gs->inactive, r, c)){
            valid = true;
        }
    }

    if (valid) {
        // valid then move the new position and merge into display
        merge(gs->active, gs->inactive, gs->display, r, c, block->block_name);
        // set new offset
        *block->offset = *poffset;
        if (mode == 0){
            // set new rotation
            block->rot = rot;
        }
    }else{
        // return to previous state
        form_active_screen(gs->active, block_coor, block->offset, r, c);
        if (mode == 1){
            // merge into the inactive screen
            merge(gs->active, gs->inactive, gs->inactive, r, c, block->block_name);
            // generate a new block
            get_random_block(block);
            // flush the active matrix
            reset_zero(gs->active, r, c);
        }
    }
    free(poffset);
}                   

block* init_block(void){
    block *b = (block *) malloc(sizeof(block));
    get_random_block(b);
    return b;
}

game_state* empty_game_state(int r, int c){
    game_state *gs = (game_state *)malloc(sizeof(game_state));
    gs->display = (int *)calloc(3 * r * c, sizeof(int));
    gs->active = (int *)calloc(r * c, sizeof(int));
    gs->inactive = (int *)calloc(3 * r * c, sizeof(int));
    return gs;
}

int demo(){
    // random seed
    time_t t;
    srand((unsigned) time(&t));

    // initialise integers
    int r, c;

    // game dimensions
    r = 20;
    c = 10;

    block *block = init_block();
    game_state *gs = empty_game_state(r, c);

    int N = 100;

    for (int t = 0; t < N; t ++){
        printf("\e[1;1H\e[2J");
        step(gs, r, c, block, 0, 0, 1);
        step(gs, r, c, block, rand() % 4, -1, 0);
        
        disp_matrix(gs->display, r, c);
        delay(100);
    }
    return 0;
}