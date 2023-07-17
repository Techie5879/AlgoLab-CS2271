#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int N = 1000000;


// function to swap two elements in an array and increment count
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    
}

// function to partition the array and return the index of pivot element
int partition(int arr[], int low, int high, int *count) {
    // randomly select a pivot element and swap it with the last element
    int random = low + rand() % (high - low);
    swap(&arr[random], &arr[high]);
    (*count)++;

    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    (*count)++;
    return i + 1;
}

// function to perform Quicksort on the array
void quicksort(int arr[], int low, int high, int *count) {
    if (low < high) {
        int pi = partition(arr, low, high, count);

        quicksort(arr, low, pi - 1, count);
        quicksort(arr, pi + 1, high, count);
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


	
	// FILE *f = fopen("./randomizedQS_uniform_obv.txt", "w");
	// FILE *f1 = fopen("./randomizedQS_uniform_avg_obv.csv", "w");

    FILE *f = fopen("./randomizedQS_normal_obv.txt", "w");
	FILE *f1 = fopen("./randomizedQS_normal_avg_obv.csv", "w");
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
            if (size <= 8) {
            	for (int i = 0; i < size; i++) {
            		printf("%d ", subset[i]);
            	}
            }
            clock_t start = clock();
            quicksort(subset, 0, size - 1, &count);
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
