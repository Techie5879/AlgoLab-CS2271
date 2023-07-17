#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int ELEMENTS = 10e6;

int main(void) {
	
	srand(time(0));
	int rangeHigh = 100;
	int rangeLow = 0;
	int range = rangeHigh - rangeLow;
	FILE *f = fopen("rand_normal.csv", "w");
	
	for (int i = 0; i < ELEMENTS; i++) {
		
        int sum = 0;
        for (int j = 0; j < 10; j++) {
            int rand_int = rand() % range + rangeLow;
            sum += rand_int;
        }
		sum /= 10;
		fprintf(f, "%d\n", sum);
	}
	fclose(f);
}



