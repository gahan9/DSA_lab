#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define TEST_NUM 1000

int* generate_array(int max_element){
    // generate array of n elements
    static int array[TEST_NUM];
    for(int i=0; i < max_element; i++){
        array[i] = rand();
    }
    return array;
}

int display_array(int *array, int no_of_elements){
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
    for(int i=0; i<no_of_elements; i++){
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

char* readline() {
    // read file line -- copied from hackerrank challange template solution
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line) { break; }
        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }
        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);
        if (!data) { break; }
        alloc_length = new_length;
    }
    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }
    data = realloc(data, data_length);
    return data;
}

void read_file_input() {
    // under development function to read inputs from file
    int ptr[TEST_NUM], count = 0, i, ar_count;
    char c[100];
    FILE *fp = fopen("file.in", "r");

    char in = fgetc(fp);
    ar_count = (int) (in - '0');
    printf("arr cnt : %d", ar_count);
    char* ar_count_str = readline();
    // fgets(c, 1024, fp);
    int cnt = 0;
    while (1) {
        printf("cnt: %d", cnt);
        cnt++;
        if (cnt >20)
            break;
        if (fgets(c,150, fp) == NULL) break;
        i++;
        printf("%3d: %s", i, c);
    }
    printf("%d\n",i);
    // while((in = fgetc(fp)) != EOF)
    //     printf("in: %c", in);
    
    char** ar_temp = split_string(&in);
    printf("---> %s", ar_temp[0]);
    for (int ar_itr = 0; ar_itr < 15; ar_itr++) {
        char* ar_item_endptr;
        char* ar_item_str = ar_temp[ar_itr];
        int ar_item = strtol(ar_item_str, &ar_item_endptr, 10);
        printf("-->%d. %d", ar_itr, ar_item);
        if (ar_item_endptr == ar_item_str || *ar_item_endptr != '\0') { exit(EXIT_FAILURE); }

        c[ar_itr] = ar_item;
    }

    // while (in != EOF){
    //     // ptr[count] = in;
    //     // fgetc(fp);
    //     in = readline();
    //     count += 1;
    // }
    // fscanf(fp,"%[^\n]", c);
    // printf("Data from the file:\n%s", c);
    // fscanf(fp,"%[^\n]", c);
    // printf("Data from the file:\n%s", c);
    printf("\n\n");
    for (i=0; i<=count; i++){
        // printf("%d\n", *(ptr +i));
    }
    fclose (fp);
}

int* bubble(int* array, int no_of_elements){
    // Bubble sort algorithm
    // no_of_elements : parameter require to specify otherwise static size of array found with
//    printf("\n--------------------Bubble sort--------------------\n");
//    printf("\number of elements\t\tAlgorithm\t\n%d\t\t Bubble Sort", no_of_elements);
    int i, j;
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

int* insertion(int* array, int no_of_elements){
    // Insertion sort algorithm
//    printf("\n--------------------Insertion sort--------------------\n");
    int i, j, key;
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

int* selection(int* array, int no_of_elements){
    // Insertion sort algorithm
//    printf("\n--------------------Insertion sort--------------------\n");
    for (int i = 0; i < no_of_elements-1; i++){  // iterate up to second last element
        int min = i;  // set current index as minimum
        for (int j = i+1; j < no_of_elements; j++){  // iterate over all elements of certain range
            if(*(array + j) < *(array + min))
                min = j;  // set new minimum index scanned/iterated so far
        }
        if (min != i)
            swap(&array[i], &array[min]);  // swap minimum element scanned/iterated so far
    }
    return array;
}

int main(){
    int i, *res, *arr_ptr;
    clock_t t;
    double cpu_time_consumption;
    printf("Initializing Sorting Algorithm for %d numbers...\n", TEST_NUM);
//    arr_ptr = generate_array(TEST_NUM);  // store generated array of random TEST_NUM numbers
//    read_file_input();
////    loop for debug to check which elements are generated randomly
//    printf("\n original array elements:");
//    display_array(arr_ptr, TEST_NUM);

    // bubble sort
    t = clock();
    arr_ptr = generate_array(TEST_NUM);
    bubble(arr_ptr, TEST_NUM);
    t = clock() - t;
    cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    printf("\nBubble sort took %f amount of time", cpu_time_consumption);
    // insertion sort
    t = clock();
    arr_ptr = generate_array(TEST_NUM);
    insertion(arr_ptr, TEST_NUM);
    t = clock() - t;
    cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    printf("\nInsertion sort took %f amount of time", cpu_time_consumption);
    // selection sort
    t = clock();
    arr_ptr = generate_array(TEST_NUM);
    selection(arr_ptr, TEST_NUM);
    t = clock() - t;
    cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    printf("\nSelection sort took %f amount of time", cpu_time_consumption);

    // display_array(res, TEST_NUM);
    printf("\n\n-*-*-*-*-*-*-*-*-*-END OF PROGRAM*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    return 0;
}
