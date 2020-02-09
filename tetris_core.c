#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "blocks.h"

struct offset{
    int i, j;
};

void disp_matrix(int *mat, int r, int c){
    int i, j;
    printf("[");
    for (i=0; i<r; i++){
        if (i != 0) printf(" ");
        printf("[");
        for (j=0; j<c; j++){
            printf("%d", *(mat + i*c + j));
            if (j != c - 1) printf(",");
        }
        printf("]");
        if (i != r - 1) printf(",\n");

    }
    printf("]\n");
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

void merge(int *arr, int *block, struct offset *o, int r, int c){
    int i, j, x;

    for (int k = 0; k < 16; k++){
        i = k % 4 + (o->i);
        j = (int)floor(k / 4) + (o->j);
        if (*(arr + i*c + j) == 0 )
            *(arr + i*c + j) = block[k];
    }
}

bool check_collide(int *arr, int *block, struct offset *o, int r, int c){
    int i, j, x;

    for (int k = 0; k < 16; k++){
        i = k % 4 + (o->i);
        j = (int)floor(k / 4) + (o->j);
        // check bounds
        if (!is_inrange(i, r) || !is_inrange(j, c)) return true;

        x = *(arr + i*c + j);

        // occupying already occupied space
        if (block[k] == 1 && x == 1) return true;
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

int* deepcopy(int *arr, int n){
    int *out = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        out[i] = *(arr + i);
    }
    return out;
}

int main(){
    // random seed
    time_t t;
    srand((unsigned) time(&t));
    int r, c, i, j;
    int num_blocks = 7;
    int num_rotations = 4;
    int *base;
    int *display;
    int *block = (int*)malloc(sizeof(stdblocks[0].pos));
    int block_num, rot;

    // game dimensions
    r = 20;
    c = 10;


    // rotation num
    rot = 0;

    struct offset *offset, poffset, o;

    offset = &o;

    offset->i = 0;
    offset->j = 3;

    base = zeros(r, c);

    int N = 10;


    get_random_block(block);
    for (int t=0; t < N; t++){
        // copying data through
        display = deepcopy(base, r * c);
        poffset = *offset;
        fall(offset);
        if (!check_collide(display, &block[rot], offset, r, c)){
            merge(display, &block[rot], offset, r, c);
        }else{
            merge(base, &block[rot], &poffset, r, c);
            get_random_block(block);
            offset->i = 0;
            offset->j = 3;
            display = deepcopy(base, r * c);
        }
        disp_matrix(display, r, c);
    }
    return 0;
}