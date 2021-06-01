#include<stdio.h>
#include<stdlib.h>
#define FACTOR (1.24733) // оптимальный константный фактор уменьшения
void output(int* arr, int arr_len){
    FILE *f;
    f = fopen("combsort.log", "a+");
    //f = fopen("C:\\Users\\Danil\\Desktop\\c\\01_sort.c\\shellsort.log", "a");
    for(int i = 0; i < arr_len; i++)
    {
        fprintf(f,"%d ",arr[i]);
    }
    fprintf(f,"\n");
    fclose(f);
}
void output2(int* arr, int arr_len){
    FILE *f;
    f = fopen("shellsort.log", "a+");
    //f = fopen("C:\\Users\\Danil\\Desktop\\c\\01_sort.c\\combsort.log", "a");
    for(int i = 0; i < arr_len; i++)
    {
        fprintf(f,"%d ",arr[i]);
    }
    fprintf(f,"\n");
    fclose(f);
}
void comb_sort(int * arr, int arr_len) {
    int gap = arr_len;
    int swaps = 1;
    int i, j;
 
    while ( gap > 1 || swaps ) {
        gap = (int)(gap / FACTOR);
        if ( gap < 1 )
            gap = 1; 
        swaps = 0; // готовность
        for ( i = 0; i < arr_len - gap; ++i ) {
            j = i + gap;
            if ( arr[i] > arr[j] ) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                output(arr, arr_len);
                swaps = 1;
            }
        }
    }
}
void shell_sort(int *arr2, int arr_len){
    for(int s=arr_len/2; s>0; s/=2) // родной шаг
        for(int i=0; i<arr_len; i++)
            for(int j=i+s; j<arr_len; j+=s)
                if(arr2[i] > arr2[j]){
                    int temp = arr2[j];
                    arr2[j] = arr2[i];
                    arr2[i] = temp;
                    output2(arr2, arr_len);
                }
}
int main(){
    FILE *f = fopen("shellsort.log", "w");
    FILE *f2 = fopen("combsort.log", "w");
    fclose(f);
    fclose(f2); // грубая очистка
    int arr_len;
    scanf("%d",&arr_len);
    int *arr = (int*)malloc(sizeof(int) * arr_len);
    int *arr2 = (int*)malloc(sizeof(int) * arr_len);
    for(int i = 0; i < arr_len; i++)
    {
        int in;
        scanf("%d",&in);
        arr[i] = in;
        arr2[i] = in;
    }
    output(arr, arr_len);
    output2(arr2, arr_len);
    comb_sort(arr, arr_len);
    shell_sort(arr2, arr_len);
    free(arr);
}
