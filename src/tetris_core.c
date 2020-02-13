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

    reset_zero(arr, r, c);

    for (int k = 0; k < 16; k++){
        i = k % 4 + (o->i);
        j = (int)floor(k / 4) + (o->j);
        if (!(is_inrange(i, r) && is_inrange(j, c))){
            return false;
        }
        *(arr + i*c + j) = block[k];
    }
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

void get_random_block(int *block){
    int n = rand() % 7;
    for (int rot = 0; rot < 4; rot++){
        for (int i = 0; i < 16; i++){
            int x = stdblocks[n].pos[rot][i];
            *(block + rot * 16 + i) = stdblocks[n].pos[rot][i];
        }
    }
}

void fall(struct offset *o){
    o->i ++;
}

void move(struct offset *o, int direction){
    o->j += direction;
}

void reset_offset(struct offset *o){
    o->i = 0;
    o->j = 3;
}

void fall_step(struct offset *offset, 
               struct offset *poffset, 
               int* active, 
               int* inactive, 
               int* display, 
               int rot, 
               int r, 
               int c, 
               int* block){
    bool valid = false;
    // save previous state
    *poffset = *offset;

    // fall down one step
    fall(offset);
    
    // Check out of bounds
    if (form_active_screen(active, &block[rot], offset, r, c)){
        // Check collisions with passive
        if (!check_collide(active, inactive, r, c)){
            valid = true;
        }
    }

    if (valid) {
        merge(active, inactive, display, r, c);
    } else {
        // Plonk down, we must have hit something right now
        form_active_screen(active, &block[rot], poffset, r, c);
        reset_offset(offset);
        merge(active, inactive, inactive, r, c);
        get_random_block(block);
        reset_zero(active, r, c);
    }
}

void move_step(struct offset *offset, 
               struct offset *poffset, 
               int* active, 
               int* inactive, 
               int* display, 
               int rot, 
               int r, 
               int c, 
               int* block,
               int dir){
    bool valid = false;
    // save previous state
    *poffset = *offset;

    // fall down one step
    move(offset, dir);
    
    // Check out of bounds
    if (form_active_screen(active, &block[rot], offset, r, c)){
        // Check collisions with passive
        if (!check_collide(active, inactive, r, c)){
            valid = true;
        }
    }

    if (valid) {
        // valid then move the new position and merge into display
        merge(active, inactive, display, r, c);
    } else {
        // do nothing, return to previous state
        form_active_screen(active, &block[rot], poffset, r, c);
        *offset = *poffset;
    }
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

    int *block = (int*)malloc(sizeof(stdblocks[0].pos));
    int block_num, rot;

    // game dimensions
    r = 20;
    c = 10;


    // rotation num
    rot = 0;

    struct offset *offset, *poffset, o, po;

    offset = &o;
    poffset = &po;

    offset->i = 0;
    offset->j = 3;

    inactive = zeros(r, c);
    active = zeros(r, c);
    display = (int *)malloc(sizeof(int) * r * c);

    int N = 40;

    get_random_block(block);
    for (int t = 0; t < N; t ++){
        fall_step(offset, poffset, active, inactive, display, rot, r, c, block);
        move_step(offset, poffset, active, inactive, display, rot, r, c, block, 1);
        disp_matrix(display, r, c);
    }


    free(inactive);
    free(active);
    free(block);
    return 0;
}