#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define QUEUESIZE 50

struct aQueue{
        int arr[QUEUESIZE];
        int head; // index of head in queue
        int tail; // index of tail in queue
};

void enqueue(int newValue, struct aQueue *queue) {
        int i;
        int j;
        if (queue->head == queue->tail) {
                // empty queue
                queue->head = 0;
                queue->tail = 1;
                queue->arr[queue->tail] = newValue;
        } else if (queue->tail + 1 % QUEUESIZE == queue->head) {
                // full queue
        } else {
                // check if we need to shift
                if (queue->tail == QUEUESIZE) {
                        // shift!
                        j = queue->tail - queue->head;
                        for (i=0; i<j; i++) {
                                queue->arr[i] = queue->arr[i+j];
                        }
                        queue->head = 0;
                        queue->tail = j;
                }
                queue->arr[queue->tail] = newValue;
                queue->tail++;
        }
        return;
}

// return the integer that is dequeued
int dequeue(struct aQueue *queue) {
        if (queue->head == queue->tail) {
                // empty list
                return 0;
        } else {
                // non-empty list
                queue->head++;
                return queue->arr[queue->head - 1];
        }
        return 0;
}

int main() {
        // as defined in class the queue is empty when head = tail
        struct aQueue ourQueue;
        ourQueue.head = 0;
        ourQueue.tail = 0;
        int i;
        int number=0;
        // enqueue three items, dequeue one, repeat 15 times
        for (i=0;i<15;i++){
                enqueue((rand() %100 + 1),&ourQueue);
                enqueue((rand()%100 + 1),&ourQueue);
        	printf("%d was dequeued\n",dequeue(&ourQueue));
        	enqueue((rand()%100 + 1),&ourQueue);
        }
        
        return 0;
}
