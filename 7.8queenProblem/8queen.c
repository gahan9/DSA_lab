// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Implementing 8-queen Problem

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../utils/constant.h"
#include "../utils/utility.h"

int sol = 1;

void pretty_print(char **board, int board_size) {
    printf("\n");

    for (register int i = 0; i < board_size; i++) {
        for (register int j = 0; j < board_size; j++)
            printf("%c", board[i][j]);
        printf("\n");
    }
}

int get_marked_col(int row_no, char **board, int board_size) {
    for (register int i=0; i < board_size; i++) {
        if(board[row_no][i] == "Q"){
            return (i);
            break;
        }
    }
}

int feasible(int row_no, int col_no, char **board, int board_size) {
    register int temp_col;
    for (register int i = 0; i < board_size; i++) {
        temp_col = get_marked_col(i, board, board_size);
        if (col_no == temp_col || abs(row_no - i) == abs(col_no - temp_col))
            return 0;
    }
    return 1;
}

void queens(int row_no, char **board, int board_size) {
    if (row_no < board_size) {
        for (register int i = 0; i < board_size; i++) {
            if (feasible(row_no, i, board, board_size)) {
                board[row_no][i] = 'Q';
                queens(row_no + 1, board, board_size);
                board[row_no][i] = '_';
            }
        }
    } else {
        printf("\n----------Solution #%d----------\n", sol);
        pretty_print(board, board_size);
        sol++;
    }
}


int main() {
    int N = 8;
    char **board = malloc(N * sizeof(char *));
    printf("###########------------------############"
           "#---------- %d queen Problem -----------#"
           "#---------------------------------------#", N);
    for (int i = 0; i < N; i++) {
        board[i] = malloc(N * sizeof(char));
        for (int j = 0; j < N; j++) {
            board[i][j] = '_';
        }
    }
    queens(0, board, N);
    return 0;
}
