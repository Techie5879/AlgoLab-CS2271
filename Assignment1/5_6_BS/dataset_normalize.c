#include <stdio.h>

const int ELEMENTS = 10e6;
const int MAX_VALUE = 100;

int main()
{
    FILE *fin = fopen("./dataset/rand_uniform.csv", "r");
    // FILE *fin = fopen("./dataset/rand_normal.csv", "r");
    
    FILE *fout = fopen("./uniform_normalized.csv", "w");
    // FILE *fout = fopen("./normal_normalized.csv", "w");


    int temp;
    long long i = 0;
    while (!feof(fin))
    {
        i++;
        fscanf(fin, "%d\n", &temp);
        fprintf(fout, "%0.2f\n", ((float)temp) / MAX_VALUE);
        printf("\r%f %% done", ((float)i) / ELEMENTS * 100);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}




