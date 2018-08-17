//
// Created by jarvis on 17/8/18.
//

#ifndef DSA_LAB_UTILITY_H
#define DSA_LAB_UTILITY_H
extern int TEST_NUM;

int* generate_array(int max_element, int sort_flag){
    // generate array of n elements

    static int* array;
    array = (int*)malloc(TEST_NUM * sizeof(int));
//    static int array[TEST_NUM];
    if (sort_flag == 0) {  // generate random unsorted numbers if flag is 0
        for (int i = 0; i < max_element; i++) {
            array[i] = rand()%100;
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

int display_array(int *array, int no_of_elements){
    // display given array of given size(no. of elements require because sizeof() returns max bound value)
    printf(": ");
    for(int i=0; i<no_of_elements; i++){
        printf( "%d ", *(array + i));
    }
    return 0;
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

#endif //DSA_LAB_UTILITY_H
