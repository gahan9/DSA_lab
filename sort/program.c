#include<stdio.h>
#include<stdlib.h>
#define TEST_NUM 1000

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

void swap(int *one, int *two)
{
    // swap function to swap elements by location/address
    int temp = *one;
    *one = *two;
    *two = temp;
}

int bubble(int* array, int no_of_elements){
    // no_of_elements : parameter require to specify otherwise static size of array found with 
    int i, j;
    // size_t arr_size = sizeof(array);
    for (j=0; j < no_of_elements-1; j++){
        for (i=0; i < no_of_elements-j-1; i++){
            if (array[i] > array[i+1]){
                swap(&array[i], &array[i+1]);
            }
        }
    }
}

int main(){
    int i, num = 100000;
    int *arr_ptr;
    /*
    int *ptr, count = 0, i;
    ptr = (int*) malloc(num * sizeof(int));
    FILE *fp = fopen("file.in", "r");
    int in = getw(fp);
	while (in != EOF){
        *(ptr + count) = in;
        printf ("%d", in);
        in = getw(fp);
        count += 1;
    }
    printf("\n\n");
    for (i=0; i<=count; i++){
        // printf("%d\n", *(ptr +i));
    }
    fclose (fp);
    */
    

    arr_ptr = generate_array(TEST_NUM);  // store generated array of random TEST_NUM numbers
    // loop for debug to check which elements are generated randomly
    // display_array(arr_ptr, TEST_NUM);
    list* lis = generate_list(TEST_NUM);
    display_list(lis);
    
    // res = bubble(&arr);
    return 0;
}
