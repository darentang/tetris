#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
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
    return (0 <= x && x <= d - 1);
}

void merge(int *arr, int *block, struct offset o, int r, int c){
    int i, j, x;

    for (int k = 0; k < 16; k++){
        i = k % 4 + o.i;
        j = floor(k / 4) + o.j;

        *(arr + i*c + j) = block[k];
    }
}

bool check_collide(int *arr, int *block, struct offset o, int r, int c){
    int i, j, x;

    for (int k = 0; k < 16; k++){
        i = k % 4 + o.i;
        j = floor(k / 4) + o.j;

        // check bounds
        if (!is_inrange(i, r) || !is_inrange(j, c)) return true;

        x = *(arr + i*c + j);

        // occupying already occupied space
        if (block[k] == 1 && x == 1) return true;
    }
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

int main(){
    time_t t;
    srand((unsigned) time(&t));

    int r, c, i, j;
    int num_blocks = 7;
    int num_rotations = 4;
    int *arr;
    int *block = (int*)malloc(sizeof(stdblocks[0].pos));
    int block_num, rot;

    r = 20;
    c = 10;
    block_num = 0;
    rot = 0;

    struct offset o = {0, 3};

    arr = zeros(r, c);

    get_random_block(block);
    merge(arr, &block[rot], o, r, c);
    disp_matrix(arr, r, c);


    return 0;
}