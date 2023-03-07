#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <globVals.h>

#include <heap.h>

struct heap *makeHeap(void){
    struct heap *newHeap = (struct heap *) malloc(sizeof(struct heap));
    newHeap->array = (struct node **) calloc(length, sizeof(struct node *));
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

void insert(struct heap *heap, struct node *newNode){
    (heap->array)[heap->size] = newNode;
    int child = heap->size;
    int parent = floor((child-1)/2);
    while(parent >= 0){
        if( (heap->array)[parent]->freq > (heap->array)[child]->freq){
            swap(heap, parent, child);
            child = parent;
            parent = floor((child-1)/2);
        }else{
            break;
        }
    }
    (heap->size)++;
}

struct node remove(struct heap*heap) {
    if(heap->size == 0){
        return NULL;
    }

    swap(heap, 0, heap->size);
    struct node *minVal = 

}