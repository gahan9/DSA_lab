// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Implementing Strassen's's Matrix Multiplication Algorithm with Divide and Conquer

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../utils/constant.h"
#include "../utils/utility.h"
#define MAX_SIZE 32

void add(int **a, int **b, int size, int **c) {
    write_log("Adding matrix\n");
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    write_log("Matrix Addition completed\n");
}

void sub(int **a, int **b, int size, int **c) {
    write_log("subtracting matrix\n");
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    write_log("Matrix Subtraction completed\n");
}

void multiply(int **c, int **d, int size, int size2, int **new){
    write_log("Multiplying Matrix...");
    if (size == 1) {
        new[0][0] = c[0][0] *d[0][0];
    }
    else {
        int i,j;
        int new_matrix_size = size/2;
        int **c11 = malloc(new_matrix_size * sizeof(int *));
        int **c12 = malloc(new_matrix_size * sizeof(int *));
        int **c21 = malloc(new_matrix_size * sizeof(int *));
        int **c22 = malloc(new_matrix_size * sizeof(int *));
        int **d11 = malloc(new_matrix_size * sizeof(int *));
        int **d12 = malloc(new_matrix_size * sizeof(int *));
        int **d21 = malloc(new_matrix_size * sizeof(int *));
        int **d22 = malloc(new_matrix_size * sizeof(int *));
        int **m1 = malloc(new_matrix_size * sizeof(int *));
        int **m2 = malloc(new_matrix_size * sizeof(int *));
        int **m3 = malloc(new_matrix_size * sizeof(int *));
        int **m4 = malloc(new_matrix_size * sizeof(int *));
        int **m5 = malloc(new_matrix_size * sizeof(int *));
        int **m6 = malloc(new_matrix_size * sizeof(int *));
        int **m7 = malloc(new_matrix_size * sizeof(int *));
        int **temp1 = malloc(new_matrix_size * sizeof(int *));
        int **temp2 = malloc(new_matrix_size * sizeof(int *));
        int **temp3 = malloc(new_matrix_size * sizeof(int *));
        int **temp4 = malloc(new_matrix_size * sizeof(int *));
        int **temp5 = malloc(new_matrix_size * sizeof(int *));
        int **temp6 = malloc(new_matrix_size * sizeof(int *));
        int **temp7 = malloc(new_matrix_size * sizeof(int *));
        int **temp8 = malloc(new_matrix_size * sizeof(int *));
        int **temp9 = malloc(new_matrix_size * sizeof(int *));
        int **temp10 = malloc(new_matrix_size * sizeof(int *));
        int **te1 = malloc(new_matrix_size * sizeof(int *));
        int **te2 = malloc(new_matrix_size * sizeof(int *));
        int **te3 = malloc(new_matrix_size * sizeof(int *));
        int **te4 = malloc(new_matrix_size * sizeof(int *));
        int **te5 = malloc(new_matrix_size * sizeof(int *));
        int **te6 = malloc(new_matrix_size * sizeof(int *));
        int **te7 = malloc(new_matrix_size * sizeof(int *));
        int **te8 = malloc(new_matrix_size * sizeof(int *));
        for(i=0; i < new_matrix_size; i++) {
            c11[i]= malloc(new_matrix_size * sizeof(int));
            c12[i]= malloc(new_matrix_size * sizeof(int));
            c21[i]= malloc(new_matrix_size * sizeof(int));
            c22[i]= malloc(new_matrix_size * sizeof(int));
            d11[i]= malloc(new_matrix_size * sizeof(int));
            d12[i]= malloc(new_matrix_size * sizeof(int));
            d21[i]= malloc(new_matrix_size * sizeof(int));
            d22[i]= malloc(new_matrix_size * sizeof(int));
            m1[i]= malloc(new_matrix_size * sizeof(int));
            m2[i]= malloc(new_matrix_size * sizeof(int));
            m3[i]= malloc(new_matrix_size * sizeof(int));
            m4[i]= malloc(new_matrix_size * sizeof(int));
            m5[i]= malloc(new_matrix_size * sizeof(int));
            m6[i]= malloc(new_matrix_size * sizeof(int));
            m7[i]= malloc(new_matrix_size * sizeof(int));
            temp1[i]= malloc(new_matrix_size * sizeof(int));
            temp2[i]= malloc(new_matrix_size * sizeof(int));
            temp3[i]= malloc(new_matrix_size * sizeof(int));
            temp4[i]= malloc(new_matrix_size * sizeof(int));
            temp5[i]= malloc(new_matrix_size * sizeof(int));
            temp6[i]= malloc(new_matrix_size * sizeof(int));
            temp7[i]= malloc(new_matrix_size * sizeof(int));
            temp8[i]= malloc(new_matrix_size * sizeof(int));
            temp9[i]= malloc(new_matrix_size * sizeof(int));
            temp10[i]= malloc(new_matrix_size * sizeof(int));
            te1[i]= malloc(new_matrix_size * sizeof(int));
            te2[i]= malloc(new_matrix_size * sizeof(int));
            te3[i]= malloc(new_matrix_size * sizeof(int));
            te4[i]= malloc(new_matrix_size * sizeof(int));
            te5[i]= malloc(new_matrix_size * sizeof(int));
            te6[i]= malloc(new_matrix_size * sizeof(int));
            te7[i]= malloc(new_matrix_size * sizeof(int));
            te8[i]= malloc(new_matrix_size * sizeof(int));
        }
        for(i=0; i < new_matrix_size; i++){
            for(j=0; j < new_matrix_size; j++){
                c11[i][j] = c[i][j];
                c12[i][j] = c[i][j+new_matrix_size];
                c21[i][j] = c[i+new_matrix_size][j];
                c22[i][j] = c[i+new_matrix_size][j+new_matrix_size];
                d11[i][j] = d[i][j];
                d12[i][j] = d[i][j+new_matrix_size];
                d21[i][j] = d[i+new_matrix_size][j];
                d22[i][j] = d[i+new_matrix_size][j+new_matrix_size];
            }
        }

        add(c11, c22, new_matrix_size, temp1);
        add(d11, d22, new_matrix_size, temp2);
        multiply(temp1, temp2, new_matrix_size, size, m1);

        add(c21, c22, new_matrix_size, temp3);
        multiply(temp3, d11, new_matrix_size, size, m2);


        sub(d12, d22, new_matrix_size, temp4);
        multiply(c11, temp4, new_matrix_size, size, m3);

        sub(d21, d11, new_matrix_size, temp5);
        multiply(c22, temp5, new_matrix_size, size, m4);

        add(c11, c12, new_matrix_size, temp6);
        multiply(temp6, d22, new_matrix_size, size, m5);

        sub(c21, c11, new_matrix_size, temp7);
        add(d11, d12, new_matrix_size, temp8);
        multiply(temp7, temp8, new_matrix_size, size, m6);

        sub(c12, c22, new_matrix_size, temp9);
        add(d21, d22, new_matrix_size, temp10);
        multiply(temp9, temp10, new_matrix_size, size, m7);

        add(m1, m7, new_matrix_size, te1);
        sub(m4, m5, new_matrix_size, te2);
        add(te1, te2, new_matrix_size, te3);    //c11

        add(m3, m5, new_matrix_size, te4);     //c12
        add(m2, m4, new_matrix_size, te5);     //c21

        add(m3, m6, new_matrix_size, te6);
        sub(m1, m2, new_matrix_size, te7);

        add(te6, te7, new_matrix_size, te8);   //c22

        int a=0;
        int b=0;
        int c=0;
        int d=0;
        int e=0;
        int nsize2 = 2*new_matrix_size;
        for(i=0; i < nsize2; i++){
            for(j=0; j < nsize2; j++){
                if(j>=0 && j<new_matrix_size && i>=0 && i<new_matrix_size){
                    new[i][j] = te3[i][j];
                }
                if(j>=new_matrix_size && j<nsize2 && i>=0 && i<new_matrix_size){
                    a=j-new_matrix_size;
                    new[i][j] = te4[i][a];
                }
                if(j>=0 && j<new_matrix_size && i>= new_matrix_size && i < nsize2){
                    c=i-new_matrix_size;
                    new[i][j] = te5[c][j];
                }
                if(j>=new_matrix_size && j< nsize2 && i>= new_matrix_size && i< nsize2 ){
                    d = i-new_matrix_size;
                    e = j-new_matrix_size;
                    new[i][j] = te8[d][e];
                }
            }
        }
    }
}

void main(){
    int size, p, itr, itr1, i, j;
    printf("Enter Size of square matrix: \n");
    scanf("%d", &size);
    printf("Size of square matrix is : %d (%d x %d)\n", size, size, size);
    int tempS = size;
    if(size & size-1 != 0){
        p = log(size)/log(2);
        size = pow(2, p+1);
    }
    int **a = malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        a[i] = malloc(size * sizeof(int));
    }
    int **b = malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        b[i] = malloc(size * sizeof(int));
    }
    printf("Enter elements of 1st matrix\n");
    for (itr = 0; itr < size; itr++) {
        for (itr1 = 0; itr1 < size; itr1++) {
            if (itr >= tempS || itr1 >= tempS)
                a[itr][itr1] = 0;
            else {
                printf("\na[%d][%d]: ", itr, itr1);
                scanf("%d", &a[itr][itr1]);
            }
        }
    }
    printf("Enter elements of 2nd matrix\n");
    for (itr = 0; itr < size; itr++) {
        for (itr1 = 0; itr1 < size; itr1++) {
            if (itr >= tempS || itr1 >= tempS)
                a[itr][itr1] = 0;
            else {
                printf("\na[%d][%d]: ", itr, itr1);
                scanf("%d", &b[itr][itr1]);
            }
        }
    }
    int **new = malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        new[i] = malloc(size * sizeof(int));
    }
    multiply(a, b, size, size, new);

    if (tempS < size)
        size = tempS;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%d   ", new[i][j]);
        }
        printf("\n");
    }
}
