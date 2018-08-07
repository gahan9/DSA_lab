#include<stdio.h>
#include<stdlib.h>
#define TEST_NUM 1000
int* generate_array(int max_element){
    // generate array of n elements
    static int array[100];
    for(int i=0; i < max_element; i++){
        array[i] = rand();
    }
    return array;
}

void swap(int *one, int *two)
{
    // swap function to swap elements by location/address
    int temp = *one;
    *one = *two;
    *two = temp;
}

int bubble(int* array){
    int temp, i, j;
    size_t arr_size = sizeof(array);
    int flag=0;
    for (j=0; j<arr_size; j++){
        for (i=0; i<arr_size; i++){
            temp = array[i];
            if (temp > array[i+1]){
                flag = 1;
                array[i] = array[i+1];
                array[i+1] = temp;
            }
        }
        if (flag == 0){
            break;
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
    
    // // loop for debug to check which elements are generated randomly
    // for(i=0; i<TEST_NUM; i++){
    //     printf( "*(arr_ptr + %d) : %d\n", i, *(arr_ptr + i));
    // }
    // res = bubble(&arr);
    return 0;
}
