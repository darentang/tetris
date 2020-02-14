#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../include/blocks.h"

struct offset{
    int i, j;
};

struct block{
    char* block_name;
    struct offset *offset;
    int rot;
    int *block_coor;
};

void delay(long miliseconds){
    
    miliseconds *= 1000;

    // Storing start time 
    clock_t start_time = clock();     

    // looping till required time is not achieved 
    while (clock() < start_time + miliseconds);
}

void disp_matrix(int *mat, int r, int c){
    int i, j;
    for (i=0; i<r; i++){
        printf("%02d[", i);
        for (j=0; j<c; j++){
            // printf("%d", *(mat + i*c + j));
            if (*(mat + i*c + j)){
                printf("#");
            }else{
                printf(" ");
            }
        }
        printf("]\n");
    }
    printf("\n");
}

int* zeros(int r, int c){
    int i, j;
    int *arr = (int*)malloc(c * r * sizeof(int));
    for (i=0; i<r; i++){
        for (j=0; j<c; j++){
            *(arr + i*c + j) = 0;
        }
    }
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
    return (0 <= x && x <= d);
}

void reset_zero(int *arr, int r, int c){
    for (int i = 0; i < r; i ++){
        for (int j = 0; j < c; j ++){
            *(arr + c * i + j) = 0;
        }
    }
}

bool form_active_screen(int *arr, int *block, struct offset *o, int r, int c){
    int i, j, x;

    int *temp_arr;
    temp_arr = (int*)malloc(16 * sizeof(int));
    reset_zero(temp_arr, r, c);

    for (int k = 0; k < 16; k++){
        i = k % 4 + (o->i);
        j = (int)floor(k / 4) + (o->j);
        if (!is_inrange(i, r) || !is_inrange(j, c)){
            free(temp_arr);
            temp_arr = NULL;
            return false;
        }
        *(temp_arr + i*c + j) = block[k];
    }
    // free(arr);
    arr = temp_arr;
    
    free(temp_arr);
    temp_arr = NULL;

    return true;
}

void merge(int* arr1, int* arr2, int* out_arr, int r, int c){
    for (int i = 0; i < r ; i ++){
        for (int j = 0; j < c; j++){
            *(out_arr + c * i + j) = *(arr1 + c * i + j) + *(arr2 + c * i + j);
            if (abs(*(out_arr + c * i + j)) > 1)
                *(out_arr + c * i + j) = 1;
        }
    }
}

bool check_collide(int* arr1, int* arr2, int r, int c){
    for (int i = 0; i < r ; i ++){
        for (int j = 0; j < c; j++){
            if (*(arr1 + c * i + j) && *(arr2 + c * i + j)){
                return true;
            }
        }
    }
    return false;
}

void reset_offset(struct offset *o){
    o->i = 0;
    o->j = 3;
}

void get_random_block(struct block *block){
    int n = rand() % 7;
    block->block_name = stdblocks[n].name;
    block->block_coor = &stdblocks[n].pos[0][0];
    block->rot = 0;
    reset_offset(block->offset);
}

void fall(struct offset *o){
    o->i ++;
}

void move(struct offset *o, int direction){
    o->j += direction;
}




void step(int* active, 
          int* inactive, 
          int* display, 
          int r, 
          int c, 
          struct block *block,
          int rot,
          int dir,
          int mode){
    

    struct offset *poffset;

    poffset = malloc(sizeof(struct offset));

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
    if (form_active_screen(active, desired_block_coor, poffset, r, c)){
        // Check collisions with passive
        if (!check_collide(active, inactive, r, c)){
            valid = true;
        }
    }

    if (valid) {
        // valid then move the new position and merge into display
        merge(active, inactive, display, r, c);

        // set new offset
        block->offset = poffset;

        // set new rotation
        block->rot = rot;

    }else{
        // return to previous state
        form_active_screen(active, block_coor, block->offset, r, c);
        if (mode == 1){
            // merge into the inactive screen
            merge(active, inactive, inactive, r, c);
            // generate a new block
            get_random_block(block);
            // // flush the active matrix
            reset_zero(active, r, c);
        }
    }
    free(poffset);
}                   


int main(){
    
    // random seed
    time_t t;
    srand((unsigned) time(&t));

    int r, c, i, j;
    int num_blocks = 7;
    int num_rotations = 4;

    int *inactive;
    int *active;
    int *display;

    // int *block = (int*)malloc(sizeof(stdblocks[0].pos));

    struct block *block;

    // game dimensions
    r = 20;
    c = 10;

    inactive = zeros(r, c);
    active = zeros(r, c);
    display = (int *)malloc(sizeof(int) * r * c);

    int N = 100;
    get_random_block(block);

    for (int t = 0; t < N; t ++){
        printf("\e[1;1H\e[2J");
        step(active, inactive, display, r, c, block, rand() % 1, 0, 1);
        step(active, inactive, display, r, c, block, rand() % 1, -1, 0);
        
        disp_matrix(display, r, c);
        delay(100);        
        
    }


    free(inactive);
    free(active);
    // free(block);
    return 0;
}