#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int ELEMENTS = 10e6;

int main(void) {
	
	srand(time(0));
	int rangeHigh = 100;
	int rangeLow = 0;
	int range = rangeHigh - rangeLow;
	FILE *f = fopen("rand_uniform.csv", "w");
	
	for (int i = 0; i < ELEMENTS; i++) {
		int rand_int = rand() % range + rangeLow;
		fprintf(f, "%d\n", rand_int);
	}
	fclose(f);
}




