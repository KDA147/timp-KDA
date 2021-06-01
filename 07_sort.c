#include<stdio.h>
#include<stdlib.h>
// триггер
// все входы-выходы если надо то поменять на нужные
void output(int* arr, int arr_len){
    FILE *f;
    f = fopen("quicksort.log", "a+");
    //f = fopen("C:\\Users\\Danil\\Desktop\\c\\01_sort.c\\quicksort.log", "a+");
    for(int i = 0; i < arr_len; i++)
    {
        fprintf(f,"%d ",arr[i]);
    }
    fprintf(f,"\n");
    fclose(f);
}
void output2(int* arr, int arr_len){
    FILE *f;
    f = fopen("heapsort.log", "a+");
    //f = fopen("C:\\Users\\Danil\\Desktop\\c\\01_sort.c\\heapsort.log", "a+");
    for(int i = 0; i < arr_len; i++)
    {
        fprintf(f,"%d ",arr[i]);
    }
    fprintf(f,"\n");
    fclose(f);
}
void qasort(int *arr, int begin, int end, int len) // qsort название конфликтует с stdlib
{
    int left = begin, right = end, base;
    base = arr[(left + right)/2];
    do
    {
        while(arr[left] < base) left++;
        while(arr[right] > base) right--;
        if(left <= right)
        {
            int tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;
            left++;
            right--;
            output(arr, len);
        }
    } while(left <= right);
    if ( begin < right )
        qsort(arr, begin, right, len);
    if ( end > left )
        qsort(arr, left, end, len);
}
void sorting_function(int *arr, int arr_len)
{
    qasort(arr, 0, arr_len-1, arr_len);
}
void sift(int *arr, int root, int bottom, int len) // делаем кучу
{
  int max; // максимальный потомок
  int done = 0; // готово не?
  while ((root * 2 <= bottom) && (!done)) 
  {
    if (root * 2 == bottom)   
      max = root * 2;   
    else if (arr[root * 2] > arr[root * 2 + 1])
      max = root * 2;
    else
      max = root * 2 + 1;
      // если элемент вершины меньше максимального потомка
    if (arr[root] < arr[max]) 
    {
      int temp = arr[root]; 
      arr[root] = arr[max];
      arr[max] = temp;
      root = max;
      output2(arr, len);
    }
    else 
      done = 1; 
  }
}
void heapSort(int *arr, int arr_len) //используем кучу
{
  for (int i = (arr_len / 2); i >= 0; i--)
    sift(arr, i, arr_len - 1, arr_len);
  for (int i = arr_len - 1; i >= 1; i--)
  {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    output2(arr, arr_len);
    sift(arr, 0, i - 1, arr_len);
  }
}
int main() {
    FILE *f = fopen("quicksort.log", "w");
    FILE *f2 = fopen("heapsort.log", "w");
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
    sorting_function(arr, arr_len);
    heapSort(arr2, arr_len);
    free(arr);
    return 0;
}
