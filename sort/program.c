#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define TEST_NUM 10000

int* generate_array(int max_element, bool sort_flag){
    // generate array of n elements
    static int array[TEST_NUM];
    if (!sort_flag) {  // generate random unsorted numbers if flag is false
        for (register int i = 0; i < max_element; i++) {
            array[i] = rand();
        }
    }
    else{
        for(register int i=1; i <= max_element; i++){  // generate sorted numbers if flag is true
            array[i] = i;
        }
    }
    return array;
}

void analysis(int* (*f)(int *, int,  int), char algo_name[]){
    int *arr_ptr;
    clock_t t;
    double cpu_time_consumption;
    printf("\nAnalysis of %s", algo_name);
    printf("\n- for unsorted %d elements: ", TEST_NUM);
    arr_ptr = generate_array(TEST_NUM, false);
    t = clock();
    (*f)(arr_ptr, 0, TEST_NUM);
    t = clock() - t;
    cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    printf("%f", cpu_time_consumption);

    printf("\n- for sorted %d elements: ", TEST_NUM);
    arr_ptr = generate_array(TEST_NUM, true);
    t = clock();
    (*f)(arr_ptr, 0, TEST_NUM);
    t = clock() - t;
    cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_consumption);

}

int display_array(int *array, int no_of_elements){
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
    for(register int i=0; i<no_of_elements; i++){
        printf( "*(array + %d) : %d\n", i, *(array + i));
    }
}

void swap(int *one, int *two){
    // swap function to swap elements by location/address
    int temp = *one;
    *one = *two;
    *two = temp;
}

char** split_string(char* str) {
    // split string by separator space
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

void read_file_input() {
    // under development function to read inputs from file
    int ptr[TEST_NUM], count = 0, i, ar_count;
    char c[100];
    FILE *fp = fopen("file.in", "r");

    char in = fgetc(fp);
    // ar_count = (int) (in - '0');
    printf("\narr\n");
     while (in != EOF){
        if ((int) (in -'0') == -16){
            printf("\nspace\n");
        }
        else{
            printf("%c - %d\n",in,  (int) (in - '0'));
        }
         in = fgetc(fp);
     }
    printf("\n\n");
    fclose (fp);
}

int* bubble(int* array, int start, int no_of_elements){
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

int* insertion(int* array, int start, int no_of_elements){
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

int* selection(int* array, int start, int no_of_elements){
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

int* quick(int *array, int start, int no_of_elements) {
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

    if (start < no_of_elements) {
        int partition_index = partition(array, start, no_of_elements);
        quick(array, start, partition_index - 1);
        quick(array, partition_index + 1, no_of_elements);
    }
    return array;
}

int* merge(int* array, int low, int high){
    // low: left start node
    // high: right end node |i.e. (number of elements - 1)

    int conquer(int array[], int low, int mid, int high){
        int array1[TEST_NUM], array2[TEST_NUM];
        int num1, num2, i, j, k;
        num1 = mid - low + 1;
        num2 = high - mid;
        for(i=0; i < num1; i++){
            array1[i] = array[low + i];
        }
        for(j=0; j < num2; j++){
            array2[j] = array[mid + j + 1];
        }

        i=0, j=0;
        for(int k=0; k<high; k++){
            if (*(array1 + i) <= *(array2 + j)){
                *(array + k) = *(array1 + i);
                i++;
            }
            else{
                *(array + k) = *(array2 + j);
                j++;
            }
        }
        return 0;
    }

    int mid;
    if (low < high){
        mid = (low + high) / 2;
        merge(array, low, mid);
        merge(array, mid+1, high);

        conquer(array, low, mid, high);
    }
    return array;
}


int main(){
    int i, *res, *arr_ptr;
    clock_t t;
    double cpu_time_consumption;
    printf("Initializing Sorting Algorithm for %d numbers...\n", TEST_NUM);
    analysis(bubble, "Bubble sort");
    analysis(insertion, "Insertion sort");
    analysis(selection, "Selection sort");
    analysis(quick, "Quick sort");
    analysis(merge, "Merge sort");
    // read_file_input();
    printf("\n\n-*-*-*-*-*-*-*-*-*-END OF PROGRAM*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    return 0;
}
