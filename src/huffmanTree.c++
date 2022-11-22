#include <bits/stdc++.h>

#include <globVals.h>

struct heap *GenerateHeap(void){
    struct heap *tempHeap = (struct heap*) malloc(sizeof(struct heap *));
    tempHeap->array = (struct node **) calloc(length, sizeof(struct node*)); //length?
    tempHeap->size = 0;
    return tempHeap;
}