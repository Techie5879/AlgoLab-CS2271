#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

const int N = 1000000;
typedef struct LL
{
    float data;
    struct LL *next;
} node;


void swap(float *a, float *b)
{
    float c = *a;
    *a = *b;
    *b = c;
}

node *LL_insert_sorted(node *list, float d, int *count) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->next = NULL;
    new_node->data = d;
    if (list == NULL) {
        list = new_node;
        (*count)++;
    }
    else if (new_node->data < list->data) {
        new_node->next = list;
        list = new_node;
        (*count)++;
    }
    else {
        node *temp = list;
        while ((temp->next != NULL) && (!((temp->data <= new_node->data) 
                    && ((temp->next)->data >= new_node->data)))) {
            temp = temp->next;
            (*count) += 2;
        }

        new_node->next = temp->next;
        temp->next = new_node;
    }
    return list;
}

node *delete_start(node *list, float *d)
{
    node *temp = list;
    list = list->next;

    *d = temp->data;
    free(temp);

    return list;
}

void bucket_sort(float *arr, int n, int *count)
{
    node *bins[n];

    for (int i = 0; i < n; i++)
        bins[i] = NULL;

    int pos = 0;

    for (int i = 0; i < n; i++)
    {
        pos = floor(n * arr[i]);

        bins[pos] = LL_insert_sorted(bins[pos], arr[i], count);
        (*count)++;
    }

    pos = 0;
    float temp;

    for (int i = 0; i < n; i++)
    {
        while (bins[i] != NULL)
        {
            bins[i] = delete_start(bins[i], &temp);
            arr[pos] = temp;
            pos++;
        }
    }
}


bool checkForCorrectness(float *arr, int length)
{
    for (int i = 0; i < length - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }

    return true;
}

void random_shuffle(float arr[],int size) {
    int i, j;

    for (i = size - 1; i > 0; i--) {
        j = rand()%(i + 1);
        swap(&arr[i], &arr[j]);
    }
}

int main() {
    srand(time(NULL));
    float *arr = malloc(N * sizeof(float));
    
    int count = 0;  // variable to keep track of number of comparisons
    
    if (arr == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    // Load the CSV file into the array
    // FILE *file = fopen("./uniform_normalized.csv", "r");
    FILE *file = fopen("./normal_normalized.csv", "r");
    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fscanf(file, "%f", &arr[i]);
    }
    fclose(file);

    // Loop over increasing powers of size 2
    // Loop over increasing powers of 2
	
	// FILE *f = fopen("./bucket_uniform_obv.txt", "w");
	// FILE *f1 = fopen("./bucket_uniform_avg_obv.csv", "w");

    FILE *f = fopen("./bucket_normal_obv.txt", "w");
	FILE *f1 = fopen("./bucket_normal_avg_obv.csv", "w");
	fprintf(f1, "size,avg_count,avg_time\n");
    const int num_iter = 100;
    for (int size = 2; size <= N; size *= 2) {
        float *subset = malloc(size * sizeof(float));
    	
        // Randomly select a set of integers from the array
        
        for (int i = 0; i < size; i++) {
            int randomIndex = rand() % N;
            subset[i] = arr[randomIndex];
        }
    	int avg_count = 0;
    	double avg_time = 0;
        for (int i = 0; i < num_iter; i++) {
            count = 0;  // reset the count for each iteration


            // Call merge sort on the subset of integers
            random_shuffle(subset, size);
            clock_t start = clock();
            bucket_sort(subset, size, &count);
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

