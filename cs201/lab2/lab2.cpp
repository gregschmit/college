#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ourData {
	float max;
	float min;
	float avg;
};

/*
** write a function calculate that:
** calculates the minimum, maximum, and average for each 
** row of the array created in main. You are given a pointer to the first
** value in the array and the number of rows and columns in the array.
** you are also given a pointer to the first structure in the array of 
** structures. All accesses to the structures or the array of data should
** utilize pointers, so no []'s should appear in your solution.
*/

void calculate(float *fltPtr,int rows,int columns, struct ourData *resPtr)
{
	int i;
	int j;
	float curCell;
	float max;
	float min;
	float avg;

	for (i = 0; i < rows; i++) {
		max = *(fltPtr + i*columns);
		min = max;
		avg = 0;
		for (j = 0; j < columns; j++) {
			curCell = *(fltPtr + (columns*i) + j);
			if (curCell > max) { max = curCell; }
			if (curCell < min) { min = curCell; }
			avg += curCell;
		}
		avg /= columns;
		(*(resPtr + i)).max = max;
		(*(resPtr + i)).min = min;
		(*(resPtr + i)).avg = avg;
	}
}

int main()
{
	float data[10][20];
	struct ourData results[10];
	int rows = 10;
	int columns = 20;
	int i,j;
	for (i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			data[i][j] = rand();
		}
	}

	calculate(&(data[0][0]),rows,columns,&(results[0]));
	
	for(i=0;i<rows;i++){
		printf("Row %d avg %f max %f min %f\n",i,results[i].avg,results[i].max,results[i].min);
	}
}
