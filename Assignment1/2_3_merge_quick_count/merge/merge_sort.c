#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const int N = 1000000;

void merge(int *arr, int initial, int mid, int final, int *count)
{
    int size1 = mid - initial + 1;
    int arr1[size1];
    for (int i = 0; i < size1; i++)
        arr1[i] = arr[initial + i];

    int size2 = final - mid;
    int arr2[size2];
    for (int i = 0; i < size2; i++)
        arr2[i] = arr[mid + 1 + i];

    int arr1_pos = 0;
    int arr2_pos = 0;
    int arr_pos = initial;
   
    // while there are elements in both arr1 and arr2
    while (arr1_pos < size1 && arr2_pos < size2) {
        if (arr1[arr1_pos] < arr2[arr2_pos]) {
            (*count)++;
            arr[arr_pos] = arr1[arr1_pos];
            arr1_pos++;
            arr_pos++;
        }
        else {
            (*count)++;
            arr[arr_pos] = arr2[arr2_pos];
            arr2_pos++;
            arr_pos++;
        }
    }

    // if arr2 exhausted
    while (arr1_pos < size1) {
        (*count)++;
        arr[arr_pos] = arr1[arr1_pos];
        arr1_pos++;
        arr_pos++;
    }

    // if arr1 exhausted
    while (arr2_pos < size2) {
        (*count)++;
        arr[arr_pos] = arr2[arr2_pos];
        arr2_pos++;
        arr_pos++;
    }
}


void merge_sort(int *arr, int initial, int final, int *count)
{
    // condition for terminating
    if (initial >= final) return;
    
    int mid = (initial + final) / 2;
    merge_sort(arr, initial, mid, count);
    merge_sort(arr, mid + 1, final, count);
    merge(arr, initial, mid, final, count);

}

bool is_array_sorted(int *arr, int length)
{
    for (int i = 0; i < length - 1; i++)
        if (arr[i] > arr[i + 1])
            return false;

    return true;
}


int main() {
    srand(time(NULL));
    int *arr = malloc(N * sizeof(int));
    
    int count = 0;  // variable to keep track of number of comparisons
    
    if (arr == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    // Load the CSV file into the array
    // FILE *file = fopen("./dataset/rand_uniform.csv", "r");
    FILE *file = fopen("./dataset/rand_normal.csv", "r");
    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    // Loop over increasing powers of size 2
    // Loop over increasing powers of 2
	
	// FILE *f = fopen("./merge_uniform_obv.txt", "w");
	// FILE *f1 = fopen("./merge_uniform_avg_obv.csv", "w");

    FILE *f = fopen("./merge_normal_obv.txt", "w");
	FILE *f1 = fopen("./merge_normal_avg_obv.csv", "w");
	fprintf(f1, "size,avg_count,avg_time\n");
    const int num_iter = 100;
    for (int size = 2; size <= N; size *= 2) {
    	
    	int avg_count = 0;
    	double avg_time = 0;
        for (int i = 0; i < num_iter; i++) {
            count = 0;  // reset the count for each iteration
            int *subset = malloc(size * sizeof(int));

            // Randomly select a set of integers from the array
            
            for (int i = 0; i < size; i++) {
                int randomIndex = rand() % N;
                subset[i] = arr[randomIndex];
            }

            // Call merge sort on the subset of integers
            clock_t start = clock();
            merge_sort(subset, 0, size - 1, &count);
            clock_t end = clock();
            double elapsedTime = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
			printf("Size: %d, Run: %d, Comparisons: %d, Time: %f\n", size, i + 1, count, elapsedTime);
            // Print the number of comparisons and elapsed time to the file
            fprintf(f, "Size: %d, Run: %d, Comparisons: %d, Time: %f\n", size, i + 1, count, elapsedTime);
            free(subset);
            avg_count += count;
            avg_time += elapsedTime;
        }
        avg_count /= num_iter;
        avg_time /= num_iter;
        fprintf(f1, "%d,%d,%f\n", size, avg_count, avg_time);
        
    }
    fclose(f);
	fclose(f1);

    
    return 0;
}
