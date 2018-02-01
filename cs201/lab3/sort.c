#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void bubblesort(int data[100], int numelements)
{
        int i,j,swap;
        int compares, swaps;
        compares = 0;
        swaps = 0;
        for (i = 0 ; i < ( numelements - 1 ); i++) {
                for (j = 0 ; j < (numelements - i - 1); j++) {
                        if (data[j] > data[j+1]) {
                                swap       = data[j];
                                data[j]   = data[j+1];
                                data[j+1] = swap;
                                swaps++;
                        }
                        compares++;
                }
        }
        printf("Bubble Sort for %d elements produces %d compares and %d"
                " swaps\n", numelements, compares, swaps);
}

void selsort(int data[100], int numelements)
{
        int i,j;
        int min;
        int compares, swaps;
        compares = 0;
        swaps = 0;
        for (i=0;i<numelements;i++) {
                min = i;
                for (j=i;j<numelements;j++) {
                        if (data[j]<data[min]) {
                                min =j;
                        }
                        compares++;
                }
                // swap position min and position i
                int tmp = data[i];
                data[i] = data[min];
                data[min] = tmp;
                swaps++;
        }
        printf("Selection Sort for %d elements produces %d compares and %d"
                " swaps\n", numelements, compares, swaps);
}

int main()
{
        const int size = 1000;
        int i;
        int rint[size];
        int rintb[size];
        int rints[size];
        srand(time(0));
        for (i=0; i<size; i++) {
                rint[i] = rand() % 10001;
                rintb[i] = rint[i];
                rints[i] = rint[i];
        }
        selsort(rints, size);
        bubblesort(rintb, size);
}
