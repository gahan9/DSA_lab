// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Implementing Strassen's's Matrix Multiplication Algorithm with Divide and Conquer

#include <stdio.h>
#include <stdlib.h>
#include "../utils/constant.h"
#include "../utils/utility.h"

#define MAX 2048

//int ONE[MAX][MAX];
//int ONE[MAX][MAX] = {{1,0,0,0}, {1,2,3,4}, {0,1,0,1}, {2,2,5,10}};
//int TWO[MAX][MAX] = {{1,0,3,8}, {2,5,5,4}, {8,1,8,3}, {9,9,5,10}};
//int TWO[MAX][MAX];
//int RESULT[MAX][MAX];
int **ONE, **TWO, **RESULT;

int ** matrix_add(int **matrix1, int **matrix2, int size){
    int **ans;
    for (int i=0; i < size; i++){
        for (int j=0; j < size; j++){

        }
    }
    return ans;
}


void conquer(int **matrix, int operational_size){
    RESULT;
}


void strassen_multiply(int **matrix1, int **matrix2, int operational_size, int offset_i, int offset_j){
    if (operational_size == 2){
        // Apply strassen multiplication
        int mul1, mul2, mul3, mul4, mul5, mul6, mul7;
        int a, b, c, d, e, f, g, h;
        a = matrix1[offset_i][offset_j];
        b = matrix1[offset_i][offset_j+1];
        c = matrix1[offset_i+1][offset_j];
        d = matrix1[offset_i+1][offset_j+1];
        e = matrix2[offset_i][offset_j];
        f = matrix2[offset_i][offset_j+1];
        g = matrix2[offset_i+1][offset_j];
        h = matrix2[offset_i+1][offset_j+1];

        mul1 = a * (f-h);
        mul2 = (a + b) * h;
        mul3 = (c + d) * e;
        mul4 = d * (g - e);
        mul5 = (a + d) * (e + h);
        mul6 = (b - d) * (g + h);
        mul7 = (a - c) * (e + f);

        RESULT[offset_i][offset_j] = mul5 + mul4 - mul2 + mul6;
        RESULT[offset_i][offset_j+1] = mul1 + mul2;
        RESULT[offset_i+1][offset_j] = mul3 + mul4;
        RESULT[offset_i+1][offset_j+1] = mul1 + mul5 - mul3 - mul7;
    }
    else{
        strassen_multiply(matrix1, matrix2, operational_size/2, 0, 0);
        strassen_multiply(matrix1, matrix2, operational_size/2, operational_size/2, 0);
        strassen_multiply(matrix1, matrix2, operational_size/2, 0, operational_size/2);
        strassen_multiply(matrix1, matrix2, operational_size/2, operational_size/2, operational_size/2);
    }
}

int main(int argc, char *argv[]){
    int array_size=4;
    if (argv[1])
        array_size = atoi(argv[1]);
    printf("array size: %d\n", array_size);
//    ONE[4][4] = {{1,0,0,0}, {1,2,3,4}, {0,1,0,1}, {2,2,5,10}};
    int i;
    //------------------ Memory Allocation
    int **ONE = (int **)malloc(array_size * sizeof(int *));
    int **TWO = (int **)malloc(array_size * sizeof(int *));
    int **RESULT = (int **)malloc(array_size * sizeof(int *));
    for (i=0; i<array_size; i++) {
        ONE[i] = (int *) malloc(array_size * sizeof(int));
        TWO[i] = (int *) malloc(array_size * sizeof(int));
        RESULT[i] = (int *) malloc(array_size * sizeof(int));
    }

    for(i=0; i<array_size; i++){
        for(int j=0; j<array_size; j++) {
            ONE[i][j] = 1;
            TWO[i][j] = 1;
            RESULT[i][j] = 0;
        }
    }
    printf("Printing ONE\n");
    display_2d_array(ONE, array_size);
    printf("Printing TWO\n");
    display_2d_array(TWO, array_size);

    strassen_multiply(ONE, TWO, array_size, 0, 0);
    printf("RESULT----\n");
    display_2d_array(RESULT, array_size);
    return 1;
}