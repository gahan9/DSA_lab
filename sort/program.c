#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define TEST_NUM 10

typedef struct list {
    int val;
    struct list* next;
} list;

int* generate_array(int max_element){
    // generate array of n elements
    static int array[100];
    for(int i=0; i < max_element; i++){
        array[i] = rand();
    }
    return array;
}

int display_array(int *array, int no_of_elements){
    for(int i=0; i<no_of_elements; i++){
        printf( "*(array + %d) : %d\n", i, *(array + i));
    }
}

list* generate_list(int max_element){
    int i;
    list * head = NULL;
    head = malloc(sizeof(list));
    head->val = rand();
    head->next = malloc(sizeof(list));
    for(int i=1; i < max_element; i++){
        i = rand();
        printf("elem: %d\n", i);
        head->next->val = i;
        head->next = malloc(sizeof(list));
    }
    head->next->next = NULL;
    return head;
}

int display_list(list* lis){
    list* current = lis;
    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

void swap(int *one, int *two){
    // swap function to swap elements by location/address
    int temp = *one;
    *one = *two;
    *two = temp;
}

char** split_string(char* str) {
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

void read_file_input()
{
    int ptr[TEST_NUM], count = 0, i;
    char c[100];
    FILE *fp = fopen("file.in", "r");
    char* in = readline();
        printf("%s\n", in);
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
    // no_of_elements : parameter require to specify otherwise static size of array found with
    printf("\n--------------------Bubble sort--------------------\n");
    printf("\nnumber of elements\t\tAlgorithm\t\n%d\t\t\t\t\t\t Bubble Sort", no_of_elements);
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
        if (flag==false)
            break;
    }
    return array;
}

int main(){
    int i, num = 100000;
    int *arr_ptr, *res;
    clock_t t;
    double cpu_time_consumption;
    printf("Initializing...\n");
    read_file_input();
    arr_ptr = generate_array(TEST_NUM);  // store generated array of random TEST_NUM numbers
    // // loop for debug to check which elements are generated randomly
    // display_array(arr_ptr, TEST_NUM);
    t = clock();
    // res = bubble(arr_ptr, TEST_NUM);
    // t = clock() - t;
    // cpu_time_consumption = ((double) (t)) / CLOCKS_PER_SEC;
    // printf("\nBubble sort took %f amount of time\n", cpu_time_consumption);
    // display_array(res, TEST_NUM);
    return 0;
}
