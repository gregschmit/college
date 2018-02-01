/*
 * Programmer:  Gregory N. Schmit
 * Date:        20160604
 * Program:     Game of Life Engine
 * Description: Backend engine for the game of life.
 */

#include <stdlib.h>

int nextstate(int **g0, int x, int y)
{
        /*
         * This method can only be called on cells that are NOT on boundary!
         * -gns
         */

        int neighbors;
        int alive;
        neighbors = 0;
        alive = 0;
        int i;
        int j;

        for (i = -1; i <= 1; i++) {
                for (j = -1; j <= 1; j++) {
                        if (g0[x + i][y + j] && (i || j)) {
                                neighbors++;
                        }
                }
        }

        if (g0[x][y]) {
                if (neighbors == 2 || neighbors == 3) { alive = 1; }
        } else {
                if (neighbors == 3) { alive = 1; }
        }

        return alive;
}

int **nextgen(int **g0, int lenx, int leny)
{
        /*
         * This will NOT change the borders, which should be 0. Also,
         * arrays-of-arrays are sometimes array[y][x], but I use array[x][y].
         * Don't worry, I loop through in a sensible way to allow memory caches
         * to be utilized coherently. -gns
         */

        int **g1;
        g1 = malloc(lenx*sizeof(*g1));
        int i;
        int j;

        for (i = 0; i < lenx; i++) {
                *(g1 + i) = malloc(leny*sizeof(**g1));
        }

        for (i = 1; i < lenx - 1; i++) {
                for (j = 1; j < leny - 1; j++) {
                        g1[i][j] = nextstate(g0, i, j);
                }
        }

        return g1;
}
