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

    return 1;
}