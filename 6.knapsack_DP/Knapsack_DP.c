// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Implementing Knapsack Problem with Dynamic Programming

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../utils/constant.h"
#include "../utils/utility.h"

int knapsack(int max_weight, int *weight, int *value, int total_elements) {
    // Returns the maximum value that can be put in a knapsack(bag) of capacity max_weight
    int **KnapsackMatrix = malloc((total_elements+1) * sizeof(int *));
    for (int i=0; i < total_elements + 1; i++){
        KnapsackMatrix[i] = malloc((max_weight + 1) * sizeof(int));
    }

    // Build table KnapsackMatrix[][]
    for (int i = 0; i <= total_elements; i++) {
        for (int w = 0; w <= max_weight; w++) {
            if (i==0 || w==0) {
                // make initial knapsack matrix row and column to zero
                KnapsackMatrix[i][w] = 0;
            }
            else if (weight[i-1] <= w) {
                // select either previously selected one or
                KnapsackMatrix[i][w] = max(value[i - 1] + KnapsackMatrix[i - 1][w - weight[i - 1]],
                                           KnapsackMatrix[i - 1][w]
                                          );
            }
            else {
                // keep previously calculated value in knapsack matrix
                KnapsackMatrix[i][w] = KnapsackMatrix[i - 1][w];
            }
        }
    }
    // return last value of knapsack matrix as it is the result of optimal value of knapsack
    return KnapsackMatrix[total_elements][max_weight];
}

int main() {
    int number_of_elements = 15;
    int max_weight = 50 + rand() % 100;
    printf("Number of elements in knapsack : %d\n", number_of_elements);
    printf("Max knapsack weight : %d\n", max_weight);
    int *value = malloc(number_of_elements * sizeof(int));
    int *weight = malloc(number_of_elements * sizeof(int));
    printf("Knapsack \nweight \t value\n");
    for (int i=0; i<number_of_elements; i++) {
        value[i] = 5 + rand() % 600;
        weight[i] = 1 + rand() % 100;
        printf("%d\t%d\n", weight[i], value[i]);
    }
    printf("\nOptimal Profit Value = %d", knapsack(max_weight, weight, value, number_of_elements));
    return 0;
}
