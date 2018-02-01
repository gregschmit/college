/*
 * This program implements a calculator that processes calculations in a file. I
 *      am currently supporting 100 rows of properly formatted data.
 *
 * Class: CS 201, Fall 2016
 * System: vi/Clang/LLVM, FreeBSD amd64
 * @author Gregory N. Schmit
 * @version Sept. 9, 2016
 */

#include <stdlib.h>
#include <stdio.h>

const float EPSILON = 0.0001;

struct rstats {
        char *id;
        int numnonzero;
        float percentnonzero;
};

struct cstats {
        float min;
        float max;
        float mean;
        float median;
};

void printarray(float *array, int size)
{
        int i;
        for (i=0; i<size; i++) {
                printf("%.2f\t",*(array+i));
        }
        printf("\n");
        return;
}

void selection_sort(float *array, int size)
{
        int i;
        int j;
        int maxindex;
        float max;
        for (i=0; i<size; i++) {
                maxindex = 0;
                max = *array;
                for (j=0; j<size-i; j++) {
                        if (*(array + j) > max) {
                                maxindex = j;
                                max = *(array + maxindex);
                        }
                }
                *(array+maxindex) = *(array+size-i-1);
                *(array+size-i-1) = max;
        }
        return;
}

int csdata_inputfileparse(char *filename, float **dataout, int *rows, int *cols,
        struct rstats **rowstats, struct cstats **colstats)
{
        // PRE: dataout must be large enough to contain COLUMNS*ROWS floats,
        //      and id fields must be able to hold ROWS strings <256 chars; no
        //      realloc. We must be passed the initial position of the
        //      data/header arrays
        // PST: return 0 if good, 1 on error
        int i;
        int j;
        int r;
        FILE *file;
        int numnonzero;
        float percentnonzero, max, min, median, mean, tmp;
        float *tmpcolumn;
        
        // open the file; if not, exit
        if (!(file = fopen(filename, "r"))) { return 1; }
        
        // read first 2 elements, which should be ints (rows and cols)
        if (!fscanf(file, "%d", rows)) { return 1; }
        if (!fscanf(file, "%d", cols)) { return 1; }
        
        // it's malloc time
        *dataout = calloc(*rows**cols, sizeof(**dataout));
        *rowstats = malloc(*rows*sizeof(**rowstats));
        r = *rows;
        for (i=0; i<r; i++) {
                (*rowstats + i)->id = malloc(26*sizeof(*((*rowstats)->id)));
        }
        *colstats = malloc(*cols*sizeof(**colstats));
        tmpcolumn = malloc(*rows*sizeof(*tmpcolumn));
        
        // now read in from the file and put the first column in the headers
        //      array and the remaining cols columns into the dataout array
        // Also, do _row_ statistics in this step for the sake of speed
        i = 0;          //rows
        while (i<*rows && fscanf(file, "%25s%*s", (*rowstats + i)->id)) {
                j = 0;  //columns
                printf("  %26s  ", (*rowstats + i)->id);
                numnonzero = 0;
                while (j<*cols &&
                        fscanf(file, "%f", *dataout + i**cols + j)) {
                        tmp = *(*dataout + i**cols + j);
                        if (tmp > EPSILON || tmp < 0-EPSILON) { numnonzero++; }
                        j++;
                }
                (*rowstats + i)->numnonzero = numnonzero;
                printf("  %10d  ", numnonzero);
                (*rowstats + i)->percentnonzero = ((float)numnonzero /
                        (float)*cols) * 100.0;
                printf("  %10.*f  \n", 2, (*rowstats + i)->percentnonzero);
                i++;
        }
        
        // print labels for row stats at bottom as in example
        printf("                               number non-    %% non-zero\n");
        printf("                               zero values      values\n");
        
        // for each col, load into tmpcolumn, sort, get stats, load stats
        for (i=0; i<*cols; i++) {
                r = 0;
                for (j=0; j<*rows; j++) {
                        tmp = *(*dataout + i + j**cols);
                        if (tmp > EPSILON || tmp < 0-EPSILON) {
                                *(tmpcolumn + r) = *(*dataout + i + j**cols);
                                r++;
                        }
                }
                
                // sort
                selection_sort(tmpcolumn, r);
                
                // calc stats
                max = *tmpcolumn;
                min = max;
                mean = 0;
                for (j=0; j<r; j++) {
                        tmp = *(tmpcolumn + j);
                        if (tmp > max) { max = tmp; }
                        if (tmp < min) { min = tmp; }
                        mean+=tmp;
                        if (j == r/2) {
                                if (r % 2) {
                                        // at midpoint
                                        median = tmp;
                                } else {
                                        // at lower midpoint, need to avg w/ +1
                                        tmp+=*(tmpcolumn+j-1);
                                        tmp/=2;
                                        median = tmp;
                                }
                        }
                }
                mean/=r;
                
                // load stats in data structure
                (*colstats + i)->max = max;
                (*colstats + i)->min = min;
                (*colstats + i)->mean = mean;
                (*colstats + i)->median = median;
        }
        
        // print colstats
        printf("\n");
        printf(" %10s ", "value");
        for (i=0; i<*cols; i++) {
                printf(" %10d ", i+1);
        }
        printf("\n");
        printf(" %10s ", "mean");
        for (i=0; i<*cols; i++) {
                printf(" %10.2f ", (*colstats + i)->mean);
        }
        printf("\n");
        printf(" %10s ", "median");
        for (i=0; i<*cols; i++) {
                printf(" %10.2f ", (*colstats + i)->median);
        }
        printf("\n");
        printf(" %10s ", "min");
        for (i=0; i<*cols; i++) {
                printf(" %10.2f ", (*colstats + i)->min);
        }
        printf("\n");
        printf(" %10s ", "max");
        for (i=0; i<*cols; i++) {
                printf(" %10.2f ", (*colstats + i)->max);
        }
        printf("\n\n");
        
        // close file and collect garbage
        fclose(file);
        free(tmpcolumn);
        return 0;
}

int main()
{
        int i;
        char *inputfilename;
        inputfilename = malloc(256);
        float *data;
        int rows;
        int cols;
        struct rstats *rowstats;
        struct cstats *colstats;
        
        printf("Greg's Statistical Calculator (CS 201 Fall 2016, v20160909)\n\n"
                "Enter the filename in the current working directory: ");
        scanf("%s", inputfilename);
        if (csdata_inputfileparse(inputfilename, &data, &rows,
                &cols, &rowstats, &colstats)) {
                free(inputfilename);
                printf("Error: data file insufficient (doesn't exist, bad"
                        " permissions, or not enough columns/rows\n");
                return 0;
        }
        
        // Garbage collection
        free(inputfilename);
        free(data);
        for (i=0;i<rows;i++) {
                free((rowstats + i)->id);
        }
        free(rowstats);
        free(colstats);
        return 0;
}
