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

void swap(struct heap *heap, int parentIndex, int childIndex){
    struct node *temp = (heap->array)[parentIndex];
    (heap->array)[parentIndex] = (heap->array)[childIndex];
    (heap->array)[childIndex] = temp;
}

void insert(struct heap *heap, struct node *){
    (heap->array)[heap->size] = node;
    int child = heap->size;
    int parent = floor((child-1)/2);
    while(parent->size != 0){
        if( (heap->array)[parent]->weight > (heap->array)[child]->weight){
            swap(heap, parent, child);
            child = parent;
            parent = floor((child-1)/2);
        }else{
            break;
        }
    }
}

void remove(struct heap*heap) {
    //po po popopopoopo
}