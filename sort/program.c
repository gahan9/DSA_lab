/*
 sorting algorithm analysis
 algorithms:
 graph: (total number v/s total time)
        sorted
        reverse sorted
        unsorted
    logarithmic scale (for variation in density)
 */
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define TEST_NUM 50
#include "utility.h"
#include "sorting_algorithms.h"

//int TEST_NUM = 10;


int* generate_array(int max_element, int sort_flag){
    // generate array of n elements

//    static int* array;
//    array = (int*)malloc(TEST_NUM * sizeof(int));
    static int array[TEST_NUM];
    if (sort_flag == 0) {  // generate random unsorted numbers if flag is 0
        for (register int i = 0; i < max_element; i++) {
            array[i] = rand();
        }
    }
    else if (sort_flag == 1){
        for(int i=0; i < max_element; i++){  // generate sorted "ascending" numbers if flag is true
            array[i] = i;
        }
    }
    else if (sort_flag == 2){
        for(int i=max_element; i > 0; i--){  // generate sorted "descending" numbers if flag is true
            array[max_element-i] = i;
        }
    }
    else{
        for(int i=0; i < max_element; i++){  // all elements same
            array[i] = sort_flag;
        }
    }
    return array;
}

void analysis(int* (*f)(int *, int,  int, int), char algo_name[]){
    int *arr_ptr;
    clock_t t;
    double cpu_time_consumption;
    int number = TEST_NUM;
    if (algo_name == "Merge sort (Recursive)")
        number = TEST_NUM - 1;
    printf("\nAnalysis of %s", algo_name);
    // unsorted elements
    arr_ptr = generate_array(number, 0);
    display_array(arr_ptr, number);
    printf("\n- for unsorted %d elements: ", TEST_NUM);
    t = clock();
    (*f)(arr_ptr, 0, number, number);
    t = clock() - t;
    cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    printf(":: %f", cpu_time_consumption);
    display_array(arr_ptr, number);

    // ascending sorted
    printf("\n- for sorted (Ascending) %d elements: ", TEST_NUM);
    arr_ptr = generate_array(TEST_NUM, 1);
    display_array(arr_ptr, TEST_NUM);
    t = clock();
    (*f)(arr_ptr, 0, number, number);
    t = clock() - t;
    cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    printf(":: %f\n", cpu_time_consumption);
    display_array(arr_ptr, TEST_NUM);

    // descending sorted
    printf("\n- for sorted (Descending) %d elements: ", TEST_NUM);
    arr_ptr = generate_array(TEST_NUM, 2);
    display_array(arr_ptr, TEST_NUM);
    t = clock();
    (*f)(arr_ptr, 0, number, number);
    t = clock() - t;
    cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    printf(":: %f\n", cpu_time_consumption);
    display_array(arr_ptr, TEST_NUM);

    // all elements equal
    printf("\n- for all equal %d elements: ", TEST_NUM);
    arr_ptr = generate_array(TEST_NUM, 500);
    display_array(arr_ptr, TEST_NUM);
    t = clock();
    (*f)(arr_ptr, 0, number, number);
    t = clock() - t;
    cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    printf(":: %f\n", cpu_time_consumption);
    display_array(arr_ptr, TEST_NUM);
}

int* heap_recursive(int* array, int start, int no_of_elements, int dummy){
    int* heapify(int* array, int heap_size, int idx){
        // heapify array == rearrange array to follow heap structure/rule
        // heap_size: no_of_elements
        int root = idx;  // consider given node as current possible root node
        int left = 2*idx + 1;
        int right = 2*idx + 2;

        if (left < heap_size && *(array + left) > *(array + root)){  // right child > eligible root/largest
            root = left;
        }
        if (right < heap_size && *(array + right) > *(array + root)){  // right child > eligible root/largest
            root = right;
        }
        if (root != idx){  // root node is not largest
            swap(&array[idx], &array[root]);
            heapify(array, heap_size, idx);
        }
    }
    // PROCESSING
    for (int i=(no_of_elements/2)-1; i >= 0; i--){
        heapify(array, no_of_elements, i);
    }
    for (int i=no_of_elements-1; i >=0; i--){
        // move current root to end
        swap(&array[0], &array[i]);
        heapify(array, i, 0);  // max heapify
    }
    return array;
}

int main(){
    int i, *res, *arr_ptr;
    clock_t t;
    double cpu_time_consumption;
    printf("Initializing Sorting Algorithm for %d numbers...\n", TEST_NUM);
//    analysis(bubble_iterative, "Bubble sort (Iterative)");
//    analysis(insertion_iterative, "Insertion sort (Iterative)");
//    analysis(selection_iterative, "Selection sort (Iterative)");
//    analysis(quick_recursive, "Quick sort (Recursive)");
//    analysis(merge_recursive, "Merge sort (Recursive)");
    analysis(heap_recursive, "Heap sort (Recursive)");
    // read_file_input();
    printf("\n\n-*-*-*-*-*-*-*-*-*-END OF PROGRAM*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    return 0;
}

/*
Initializing Sorting Algorithm for 10,00,000 numbers...

Analysis of Insertion sort (Iterative)
- for unsorted 1000000 elements: 374.238000
*/