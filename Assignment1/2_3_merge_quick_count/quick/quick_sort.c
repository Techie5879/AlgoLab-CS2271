#include <stdio.h>
#include <stdbool.h> //for true keyword
#include <stdlib.h>  //for rand() and srand()
#include <time.h>


const int N = 1000000;

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int partition(int *arr, int initial, int final, int *count)
{
    int pivot_value = arr[initial];

    int left_iterator = initial;
    int right_iterator = final;

    while (true)
    {
        while (arr[left_iterator] < pivot_value)
            left_iterator++;

        while (pivot_value < arr[right_iterator])
            right_iterator--;

        if (arr[left_iterator] == arr[right_iterator])
        {
            if (left_iterator == right_iterator)
                return left_iterator;
            else
                right_iterator--;
        }
        else if (left_iterator < right_iterator)
        {
            swap(&arr[left_iterator], &arr[right_iterator]);
            (*count)++;
        }
        else
            return left_iterator;
    }
}


void quick_sort(int *arr, int initial, int final, int *count)
{
    if (initial < final) {
        int pos_of_pivot = partition(arr, initial, final, count);
        quick_sort(arr, initial, pos_of_pivot, count);
        quick_sort(arr, pos_of_pivot + 1, final, count);
    }
}

void random_shuffle(int arr[],int size) {
    int i, j;

    for (i = size - 1; i > 0; i--) {
        j = rand()%(i + 1);
        swap(&arr[i], &arr[j]);
    }
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
	
	// FILE *f = fopen("./quick_uniform_obv.txt", "w");
	// FILE *f1 = fopen("./quick_uniform_avg_obv.csv", "w");

    FILE *f = fopen("./quick_normal_obv.txt", "w");
	FILE *f1 = fopen("./quick_normal_avg_obv.csv", "w");
	fprintf(f1, "size,avg_count,avg_time\n");
    const int num_iter = 100;
    for (int size = 2; size <= N; size *= 2) {
        int *subset = malloc(size * sizeof(int));

        // Randomly select a set of integers from the array
        for (int i = 0; i < size; i++) {
            int randomIndex = rand() % N;
            subset[i] = arr[randomIndex];
        }
            
    	
    	int avg_count = 0;
    	double avg_time = 0;
        for (int i = 0; i < num_iter; i++) {
            count = 0;  // reset the count for each iteration
            
            // Call quick sort on the subset of integers
            random_shuffle(subset, size); // shuffle the array before sending to QS
            clock_t start = clock();
            quick_sort(subset, 0, size - 1, &count);
            clock_t end = clock();
            double elapsedTime = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
			printf("Size: %d, Run: %d, Comparisons: %d, Time: %f\n", size, i + 1, count, elapsedTime);
            // Print the number of comparisons and elapsed time to the file
            fprintf(f, "Size: %d, Run: %d, Comparisons: %d, Time: %f\n", size, i + 1, count, elapsedTime);
            
            avg_count += count;
            avg_time += elapsedTime;
        }
        free(subset);
        avg_count /= num_iter;
        avg_time /= num_iter;
        fprintf(f1, "%d,%d,%f\n", size, avg_count, avg_time);
        
    }
    fclose(f);
	fclose(f1);

    
    return 0;
}
