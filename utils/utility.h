//
// Created by jarvis on 17/8/18.
//

#ifndef DSA_LAB_UTILITY_H
#define DSA_LAB_UTILITY_H

#include <string.h>
#include <stdarg.h>

int write_log(const char *format, ...) {
    if(DEBUG) {
        printf("\n[DEBUG_LOG]> ");
        va_list args;
        va_start (args, format);
        vprintf(format, args);
        va_end (args);
    }
}

int *get_min_max(int *array, int no_of_elements, int min_max[]){
    // get minimum and maximum of array
//    printf("elements of array: ");
    for(int i=0; i<no_of_elements; i++){
//        printf("%d ", *(array + i));
        if (*(array + i) < min_max[0])
            min_max[0] = *(array + i);
        if (*(array + i) > min_max[1])
            min_max[1] = *(array + i);
    }
    return min_max;
}

int display_array(int *array, int no_of_elements){
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
    write_log(": ");
    for(int i=0; i<no_of_elements; i++){
        write_log( "%d ", *(array + i));
    }
    return 0;
}

int show_2d_array(int **array, int no_of_elements){
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
    write_log(": ");
    for(int i=0; i<no_of_elements; i++){
        printf("a[%d][i]: ", i);
        for(int j=0; j<no_of_elements; j++) {
//            printf("array[%d][%d]: %d ", i, j, array[i][j]);
            printf("%d\t", array[i][j]);
        }
        printf("\twhere 0<=i<=%d\n", no_of_elements-1);
    }
    return 0;
}

int display_2d_array(int **array, int no_of_elements){
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
    write_log(": ");
    for(int i=0; i<no_of_elements; i++){
        printf("a[%d][]: ", i);
        for(int j=0; j<no_of_elements; j++) {
//            printf("array[%d][%d]: %d ", i, j, array[i][j]);
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    return 0;
}


void swap(int *one, int *two){
    // swap function to swap elements by location/address
    int temp = *one;
    *one = *two;
    *two = temp;
}

#endif //DSA_LAB_UTILITY_H
