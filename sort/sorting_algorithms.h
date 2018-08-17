//
// Created by jarvis on 17/8/18.
//

#ifndef DSA_LAB_SORTING_ALGORITHMS_H
#define DSA_LAB_SORTING_ALGORITHMS_H

int* bubble_iterative(int* array, int start, int no_of_elements, int dummy){
    // Bubble sort algorithm
    // no_of_elements : parameter require to specify otherwise static size of array found with
//    printf("\n--------------------Bubble sort--------------------\n");
//    printf("\number of elements\t\tAlgorithm\t\n%d\t\t Bubble Sort", no_of_elements);
    register int i, j;
    bool flag;
    // size_t arr_size = sizeof(array);
    for (j=0; j < no_of_elements-1; j++){
        flag = false;
        for (i=0; i < no_of_elements-j-1; i++){
            if (array[i] > array[i+1]){
                swap(&array[i], &array[i+1]);
                flag = true;
            }
        }
        if (!flag)
            break;
    }
    return array;
}

int* insertion_iterative(int* array, int start, int no_of_elements){
    // Insertion sort algorithm
//    printf("\n--------------------Insertion sort--------------------\n");
    register int i, j, key;
    for (i = 1; i < no_of_elements; i++){
        key = array[i];
        j = i-1;
        while (j >= 0 && array[j] > key){
            array[j+1] = array[j];
            j = j-1;
        }
        array[j+1] = key;
    }
    return array;
}

int* selection_iterative(int* array, int start, int no_of_elements){
    // Insertion sort algorithm
//    printf("\n--------------------Selection sort--------------------\n");
    for (register int i = 0; i < no_of_elements-1; i++){  // iterate up to second last element
        int min = i;  // set current index as minimum
        for (register int j = i+1; j < no_of_elements; j++){  // iterate over all elements of certain range
            if(*(array + j) < *(array + min))
                min = j;  // set new minimum index scanned/iterated so far
        }
        if (min != i)
            swap(&array[i], &array[min]);  // swap minimum element scanned/iterated so far
    }
    return array;
}

int* quick_recursive(int *array, int start, int no_of_elements) {
    no_of_elements = no_of_elements-1;
    int partition (int* array, int start, int no_of_elements) {
        int pivot = array[no_of_elements];    // select pivot
        int i = (start - 1);  // get index of smaller element

        for (int j=start; j <= no_of_elements- 1; j++) {
            if (array[j] <= pivot) {
                i++;    // increment index of smaller element
                swap(&array[i], &array[j]);
            }
        }
        swap(&array[i + 1], &array[no_of_elements]);
        return (i + 1);
    }
    // PROCESSING
    if (start < no_of_elements) {
        int partition_index = partition(array, start, no_of_elements);
        quick_recursive(array, start, partition_index - 1);
        quick_recursive(array, partition_index + 1, no_of_elements);
    }
    return array;
}

int* merge_recursive(int* array, int low, int high, int no_of_elements){
    // low: left start node
    // high: right end node |i.e. (number of elements - 1)

    void conquer(int array[], int low, int mid, int high, int no_of_elements){
        int temp[no_of_elements];
        int num1, num2, i=low, j=mid+1, k=0;
        while(i<=mid && j<=high)
        {
            if(array[i] < array[j])
                temp[k++] = array[i++];
            else
                temp[k++] = array[j++];
        }
        while(i<=mid)
            temp[k++] = array[i++];

        while(j<=high)
            temp[k++] = array[j++];

        //Transfer elements from temp[] back to a[]
        for(i=low,j=0;i<=high;i++,j++)
            array[i]=temp[j];
    }
    // PROCESSING
    int mid;
    if (low < high){
        mid = (low + high) / 2;
        merge_recursive(array, low, mid, no_of_elements);
        merge_recursive(array, mid+1, high, no_of_elements);

        conquer(array, low, mid, high, no_of_elements);
    }
    return array;
}

#endif //DSA_LAB_SORTING_ALGORITHMS_H
