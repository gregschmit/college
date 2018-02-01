#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

// heaps
// swap, insert, deleteMax, bubbleup, bubbledown
void swap(int heap[], int i, int j){
	int temp = heap[i];
	heap[i]=heap[j];
	heap[j]=temp;
}

void bubbleDown(int heap[],int position, int numelem){
	int child = 2*position;
	// need to find larger child and make sure child
	// is less than numelem
	if ((child < numelem) && (heap[child+1] > heap[child]))
		child++;
	if ((child <= numelem) && (heap[position] < heap[child])){
		swap(heap,position,child);
		bubbleDown(heap,child,numelem);
	}


}

int deleteMax(int heap[],int *numelem ){
	// swap value at 1 and numelem
	int temp = heap[1];
	swap(heap,1,*numelem);
	(*numelem)--;
	bubbleDown(heap,1,*numelem);
	return temp;
}

void bubbleUp(int heap[], int position){
// check if value at position is larger than parent, if so, swap and recurse

int parent = position/2;
if((heap[position]>heap[parent])&&(position>1)){
	swap(heap,position,parent);
	bubbleUp(heap,parent);
	}
}

void printHeap(int heap[],int numelem){
	int i;
	for(i=1;i<=numelem;i++){
		printf("i %d %d ",i, heap[i]);
	}
	printf("\n");
}

void printArr(int arr[],int numelem){
	int i;
	for(i=0;i<numelem;i++){
		printf("i %d %d ",i, arr[i]);
	}
	printf("\n");
}

void insert(int heap[], int val, int *numelem){
	// add val to heap at position numelem+1
	(*numelem)++;
	//++*numelem; valid but not sure does what we want.
//	printf("numelem %d\n",*numelem);
	heap[(*numelem)]=val;
//	printHeap(heap,*numelem);

	bubbleUp(heap,(*numelem));
}

int *HeapSortV1(int heap[], int n)
{
        if (!heap) { return 0; }
        int i;
        int heapsize;
        int *sorted_arr;
        sorted_arr = malloc(n*sizeof(*sorted_arr));
        heapsize = n;
        for (i=0; i<n; i++) {
                *(sorted_arr + i) = deleteMax(heap, &heapsize);
        }
        return sorted_arr;
}

int *makeHeap(int *arr, int arrsize)
{
        int i;
        int *heap;
        int heapsize;
        heap = malloc((arrsize+1)*sizeof(*heap));
        heapsize = 0;
        for (i=0; i<arrsize; i++) {
                insert(heap, *(arr+i), &heapsize);
        }
        return heap;
}

void HeapSort(int *arr, int n)
{
        int* heap;
        heap = makeHeap(arr, n);
        arr = HeapSortV1(heap, n);
}

int main() {

int myHeap[50];
int numelements = 0;
insert(myHeap,50,&numelements);
printHeap(myHeap,numelements);
insert(myHeap,55,&numelements);
insert(myHeap,10,&numelements);
insert(myHeap,60,&numelements);
insert(myHeap,25,&numelements);
printHeap(myHeap,numelements);
insert(myHeap,125,&numelements);
printHeap(myHeap,numelements);
insert(myHeap,65,&numelements);
printHeap(myHeap,numelements);
int val = deleteMax(myHeap,&numelements);
printHeap(myHeap,numelements);
int *arr;
arr = HeapSortV1(myHeap, numelements);
printArr(arr, numelements);
int *newHeap;
newHeap = makeHeap(arr, numelements);
printHeap(newHeap, numelements);


return 0;
}
