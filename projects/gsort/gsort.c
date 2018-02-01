/*
 * Programmer:  Gregory N. Schmit
 * Date:        20160609
 * Library:     Greg's Sorting Algorithms
 * Description: Greg's implementation of various sorting algorithms, in
 *              ascending order.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print_array(int *arr, int size)
{
        int i;
        printf("[ ");
        if (size < 100) {
                for (i = 0; i < size - 1; i++) {
                        printf("%i, ", *(arr + i));
                }
        } else {
                for (i = 0; i < 9; i++) {
                        printf("%i, ", *(arr + i));
                }
                printf("  . . .   ,");
                for (i = size - 9; i < size - 1; i++) {
                        printf("%i, ", *(arr + i));
                }
        }
        printf("%i ]\n\n", *(arr + size - 1));
}

void swap(int *arr, int pos1, int pos2)
{
        int tmp;
        tmp = *(arr + pos1);
        *(arr + pos1) = *(arr + pos2);
        *(arr + pos2) = tmp;
        return;
}

void bubble_sort(int *arr, int size)
{
        int i;
        int head;
        
        head = size;
        do {
                for (i = 1; i < head; i++) {
                        if (*(arr + i - 1) > *(arr + i)) {
                                swap(arr, i, i - 1);
                        }
                }
                head--;
                if (head % 1000 == 0) {
                        printf("head is now at %i...\n", head);
                }
        } while (head > 1);
}

int main()
{
        const int N = 1000000;
        int i;
        int arr[N];
        for (i = 0; i < N; i++) {
                arr[i] = N - i;
        }

        printf("original array: ");
        print_array(arr, N);
        char buffer[100];
        time_t now;
        now = time(0);
        strftime (buffer, 100, "%Y-%m-%d %H:%M:%S.000", localtime (&now));
        printf("%s\n", buffer);
        bubble_sort(arr, N);
        now = time(0);
        strftime (buffer, 100, "%Y-%m-%d %H:%M:%S.000", localtime (&now));
        printf("%s\n", buffer);
        printf("\nsorted array: ");
        print_array(arr, N);

        return 0;
}
