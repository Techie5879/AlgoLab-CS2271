#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void insertion_sort(int arr[], int initial, int final)
{
    for (int i = initial; i <= final; i++)
    {
        int value = arr[i];
        int pos = i - 1;
        while (pos >= initial && arr[pos] > value)
        {
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = value;
    }
}


int give_median(int arr[], int initial, int final)
{
    insertion_sort(arr, initial, final);
    int mid = (initial + final) / 2;
    return arr[mid];
}


//give arr_size as sizeof(arr)/sizeof(int)
int median_of_median(int arr[], int arr_size, int divide_size)
{
    if (arr_size < divide_size)
    {
        int median = give_median(arr, 0, arr_size - 1);
        return median;
    }

    int no_full_group = arr_size / divide_size;
    int elements_in_last = arr_size % divide_size;

    int next_arr_size;

    if (elements_in_last == 0)
        next_arr_size = no_full_group;
    else
        next_arr_size = no_full_group + 1;

    int next_arr[next_arr_size];

    for (int i = 0; i < next_arr_size; i++)
    {
        if (i == next_arr_size -1)
            next_arr[i] = give_median(arr, divide_size * i, arr_size - 1);
        else
            next_arr[i] = give_median(arr, divide_size * i, divide_size * (i + 1) - 1);
    }

    return median_of_median(next_arr, next_arr_size,divide_size);
}

void solve(FILE*fp,int arr[],int size,int direct)
{
    fprintf(fp,"Array:\n");
    for (int i = 0; i < size; i++)
        fprintf(fp,"%d ", arr[i]);
    fprintf(fp,"\n");

    fprintf(fp,"MoM: %d\n", median_of_median(arr,size,2));
    fprintf(fp,"Direct: %d\n",direct);
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


void permutation(FILE *fp,int *arr, int start, int end,int direct)
{
    if(start==end)
    {
        solve(fp,arr, end+1,direct);
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        //swapping numbers
        swap((arr+i), (arr+start));
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        permutation(fp,arr, start+1, end,direct);
        swap((arr+i), (arr+start));
    }
}


int main() {
    srand(time(0));
    FILE *fp;
    fp=fopen("MOM.txt","w");
    const int iter=10;
    for(int i=0;i<iter;i++) {
        fprintf(fp,"ITERATION NO:  %d",i+1);
        fprintf(fp,"------------------------\n");
        int arr_size = 10;
        int arr[arr_size];
        for (int i = 0; i < arr_size; i++)
            arr[i] = rand() % 10;
        int copy[arr_size];
        for (int i = 0; i < arr_size; i++)
            copy[i] = arr[i];
        int direct=give_median(copy, 0, arr_size - 1);
        permutation(fp,arr, 0, arr_size-1,direct);
    }
    fclose(fp);
    return 0;
}



