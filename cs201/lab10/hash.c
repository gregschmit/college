#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int hash1(char *string, int table_size, int salt)
{
        int i;
        int hash;
        i = 0;
        hash = 0;
        while (*(string + i)) {
                hash+=((*(string + i)*(int)pow(salt, i)) % table_size);
                i++;
        }
        return hash;
}

int hash2(char *string, int table_size)
{
        int i;
        int hash;
        i = 0;
        hash = 0;
        while (*(string + i)) {
                hash+=((*(string + i)*i) % table_size);
                i++;
        }
        return hash;
}



int main()
{
        int i;
        char **movies;
        char ignore[1000];
        int num_movies;
        FILE *file;
        movies = malloc(101*sizeof(*movies));
        for (i=0; i<101; i++) {
                *(movies + i) = malloc(101*sizeof(**movies));
        }
        printf("%p\n", file);
        file = fopen("movies.csv", "r");
        i = 0;
        fgets(ignore, 100, file);
        while (fgets(*(movies + i), 100, file)) {
                i++;
                if (i>=100) { break; }
        }
        num_movies = i;
        for (i=0; i<num_movies; i++) {
                printf("%s\n", *(movies + i));
        }
}
