// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Implementing 8-queen Problem

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int counter = 1;

int placeQueen(int *board, int row_no) {
    for (register int i = 0; i < row_no; i++) {
        if (board[i] == board[row_no])
            return false; // same column
        if ((board[i] - board[row_no]) == (row_no - i))
            return false; // same major diagonal
        if ((board[row_no] - board[i]) == (row_no - i))
            return false; // same minor diagonal
    }
    return true;
}

void pretty_print(int q[], int board_size) {
    printf("\n");
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (q[i] == j)
                printf("Q ");
            else
                printf("* ");
        }
        printf("\n");
    }
}

void queenLogic(int *queens, int row_no, int board_size) {
    if (row_no == board_size) {
        pretty_print(queens, board_size);
        if (counter % 10 == 1)
            printf("%dst solution found...\n", counter);
        else if (counter % 10 == 2)
            printf("%dnd solution found...\n", counter);
        else if (counter % 10 == 3)
            printf("%drd solution found...\n", counter);
        else
            printf("%dth solution found...\n", counter);
        counter++;
    } else {
        for (int i = 0; i < board_size; i++) {
            queens[row_no] = i;
            if (placeQueen(queens, row_no))
                queenLogic(queens, row_no + 1, board_size);
        }
    }
}

int main() {
    int board_size = 8;
    int *queens = malloc(board_size * sizeof(int));
    printf("###########------------------############\n"
           "#---------- %d queen Problem -----------#\n"
           "#---------------------------------------#\n", board_size);
    queenLogic(queens, 0, board_size);
    return 1;
}