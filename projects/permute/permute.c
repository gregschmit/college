/*
 * Programmer:  Gregory N. Schmit
 * Date:        20160601
 * Program:     Permute
 * Description: Given a C-style character array, provides a list of 
 *              character permutations as an array of character arrays.
 */

#include <stdio.h>
#include <stdlib.h>

int permute_qty(int len)
{
        if (len <= 1) {
                return 1;
        } else {
                return len*permute_qty(len-1);
        }
}

char **permute(char *pstring)
{
        char c;
        char *pstringnext;
        char **rval;
        char **permutenext;
        int i;
        int j;
        int k;
        int l;
        int len;
        int pqty;
        int pqtynext;

        i = 0;
        len = 0;
        do {
                c = *(pstring + i);
                if (c) { len++; }
                i++;
        } while (c);

        pqty = permute_qty(len);
        pqtynext = permute_qty(len - 1);
        rval = malloc(pqty*sizeof(*rval));

        if (len < 1) {
                *rval = malloc(sizeof(**rval));
                **rval = 0;
        } else if (len == 1) {
                *rval = malloc(2*sizeof(**rval));
                **rval = *pstring;
                *(*rval + 1) = 0;
        } else {
                for (i = 0; i < len; i++) {
                        j = 0;
                        k = 0;
                        pstringnext = malloc(len*sizeof(*pstringnext));
                        do {
                                if (j != i) {
                                        *(pstringnext + k) = *(pstring + j);
                                        k++;
                                }
                        j++;
                        } while (*(pstring + j) != 0);
                        *(pstringnext + k) = 0;
                        permutenext = permute(pstringnext);
                        free(pstringnext);
                        for (j = 0; j < pqtynext; j++) {
                                *(rval + (pqtynext*i + j)) = malloc((len + 1)
                                        *sizeof(**rval));
                                **(rval + (pqtynext*i + j)) = *(pstring + i);
                                *(*(rval + (pqtynext*i + j)) + len) = 0;
                                for (k = 1; k < len; k++) {
                                        *(*(rval + (pqtynext*i + j)) + k) =
                                                *(*(permutenext + j) + k - 1);
                                }
                                free(*(permutenext + j));
                        }
                        free(permutenext);
                }
        }

        return rval;
}

void permute_print(char *word)
{
        char **permutations;
        int i;
        int p;
        int len;

        i = 0;
        len = 0;
        do {
                if (*(word + i)) { len++; }
                i++;
        } while (*(word + i));

        permutations = permute(word);
        p = permute_qty(len);

        for (i = 0; i < p; i++) {
                printf("%s\n", *(permutations + i));
                free(*(permutations + i));
        }
        free(permutations);

        printf("\ntotal: %i\n", p);

        return;
}

int main(int argc, char *argv[])
{
        if (argc == 2) {
                permute_print(argv[1]);
        } else {
                printf("Correctusage is 'permute word'.\n");
        }

        return 0;
}
