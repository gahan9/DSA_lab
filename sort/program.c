#include<stdio.h>
#include<stdlib.h>
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
    int num = 100000;

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
    // res = bubble(&arr);
    return 0;
}
