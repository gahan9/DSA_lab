//
// Created by Gahan Saraiya on 1/10/18.
// Recursive Exponential algorithm using Divide and Conquer Approach
//
#include <stdio.h>
#include <stdlib.h>

int exponent(int number, int power){
    int new_power;
    // terminating condition
    if (power == 0) {
        return 1;
    }
    if (power == 1){
        return number;
    }
    else if (power == 2){
        return number * number;
    }
    else if (power > 2){
        new_power = power / 2;
        int sub_result;
        sub_result = exponent(number * number, new_power);
        // recursive exponential
        if (power % 2 == 0) {
            return sub_result;
        } else {
            return number * sub_result;
        }
    }
}

int main(int argc, char *argv[]){
    int power, result, number;
    printf("Enter Number: ");
    scanf("%d", &number);
    printf("Enter Power: ");
    scanf("%d", &power);

    // recursion call
    result = exponent(number, power);
    printf("Answer for %d ^ %d : %d\n", number, power, result);
}
