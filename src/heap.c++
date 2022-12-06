#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <globVals.h>

#include <heap.h>

struct heap *makeHeap(void){
    struct heap *newHeap = (struct heap *) malloc(sizeof(struct heap));
    newHeap->array = (struct node **) calloc(length, (struct node *));
    newHeap->size = 0;
    return newHeap;
}

void freeHeap(struct heap *heap){
    free(heap->array);
    free(heap);
}

