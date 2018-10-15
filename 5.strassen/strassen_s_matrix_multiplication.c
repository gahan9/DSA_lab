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

int ONE[MAX][MAX];
int TWO[MAX][MAX];
int RESULT[MAX][MAX];

void strassen_multiply(int matrix1[MAX][MAX], int matrix2[MAX][MAX], int operational_size, int offset_i, int offset_j){
    if (operational_size == 2){
        // Apply strassen multiplication
        int mul1, mul2, mul3, mul4, mul5, mul6, mul7;
        mul1 = (matrix1[offset_i+1][offset_i+1] + matrix1[offset_i+2][offset_i+2]) * (matrix2[offset_i+1][offset_i+1] + matrix2[offset_i+2][offset_i+2]);
        mul2 = (matrix1[offset_i+2][offset_i+1] + matrix1[offset_i+2][offset_i+2]) * (matrix2[offset_i+1][offset_i+1]);
        mul3 = (matrix1[offset_i+1][offset_i+1]) * (matrix2[offset_i+1][offset_i+2] - matrix2[offset_i+2][offset_i+2]);
        mul4 = (matrix1[offset_i+2][offset_i+2]) * (matrix2[offset_i+2][offset_i+1] - matrix2[offset_i+1][offset_i+1]);
        mul5 = (matrix1[offset_i+1][offset_i+1] + matrix1[offset_i+1][offset_i+2]) * (matrix2[offset_i+2][offset_i+2]);
        mul6 = (matrix1[offset_i+2][offset_i+1] - matrix1[offset_i+1][offset_i+1]) * (matrix2[offset_i+1][offset_i+1] + matrix2[offset_i+1][offset_i+2]);
        mul7 = (matrix1[offset_i+1][offset_i+2] - matrix1[offset_i+2][offset_i+2]) * (matrix2[offset_i+2][offset_i+1] + matrix2[offset_i+2][offset_i+2]);
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
    for(int i=0; i<array_size; i++){
        for(int j=0; j<array_size; j++) {
            ONE[i][j] = 1;
            TWO[i][j] = 1;
        }
    }
    printf("Printing ONE\n");
    show_2d_array(ONE, array_size);
    printf("Printing TWO\n");
    show_2d_array(TWO, array_size);

    strassen_multiply(ONE, TWO, array_size, 0, 0);
    printf("RESULT----\n");
    show_2d_array(RESULT, array_size);
    return 1;
}