/*
 * Programmer:  Gregory N. Schmit
 * Date:        20160604
 * Program:     Game of Life
 * Description: Simple text implementation of the game of life.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "life_engine.h"

void waitFor(unsigned int timeval)
{
        int i, j, k;
        for (i = 0; i < timeval; i++) {
                for (j = 0; j < 2000; j++) {
                        for (k = 0; k < 2000; k++) {
                                int volatile t = 120 * j * i + k;
                                t = t + 5;
                        }
                }
        }
}

int main()
{
        int gens;
        int lenx;
        int leny;
        int **g0;
        int i;
        int j;
        int t;
        int tmp;
        int delay;
        char c;

        gens = 500;
        lenx = 24;
        leny = 80;
        delay = 100;

        printf("Welcome to Greg's implementation of John Conway's Game of"
                " Life.\n\nPress ENTER to continue.\n");
        getchar();
        printf("Let's define our universe dimensions. You may want to make sure"
                " it fits in your terminal window.\nx: ");
        scanf("%i", &leny);
        printf("y: ");
        scanf("%i", &lenx);
        printf("How many generations do you want to run? ");
        scanf("%i", &gens);
        printf("What time delay do you want? (if you don't know, enter 100) ");
        scanf("%i", &delay);

        srand(time(0));
        g0 = malloc(lenx*sizeof(*g0));
        for (i = 0; i < lenx; i++) {
                *(g0 + i) = malloc(leny*sizeof(**g0));
                for (j = 0; j < leny; j++) {
                        /*
                         * The following logic simply tests is the cell is
                         * boundary, and sets it to 0. -gns
                         */
                        if (!i || i == lenx - 1 || !j || j == leny - 1) {
                                g0[i][j] = 0;
                        } else {
                                /* Else, randomize. -gns */
                                tmp = rand() % 100;
                                g0[i][j] = (tmp < 50) ? 0 : 1;
                        }
                }
        }

        for (t = 0; t < gens; t++) {
                printf("\n\n\ngeneration %i:\n", t);
                for (i = 0; i < lenx; i++) {
                        for (j = 0; j < leny; j++) {
                                if (g0[i][j]) {
                                        c = '0';
                                } else {
                                        c = '_';
                                }
                                printf("%c", c);
                        }
                        printf("\n");
                }
                waitFor(delay);
                g0 = nextgen(g0, lenx, leny);
        }

        return 0;
}
