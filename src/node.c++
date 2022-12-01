#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <globVals.h>
#include <node.h>

struct node *makeNode(unsigned char token, int freq, struct node *left, struct node *right){
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    if(newNode == NULL){
        mallocError("node.c", 0);
    }
    newNode->token = token;
    newNode->freq = freq;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

struct node **makeNode(int *vals){
    struct node **nodes = (struct node **) calloc(ASCII, sizeof(struct node *));
    if(nodes == NULL){
        mallocError("node.c", 1);
    }

    for(int i = 0 ; i < ASCII; i++){
        if(vals[i]){
            nodes[length] = makeNode( (unsigned char) i, vals[i], NULL, NULL);
            length++;
        }
    }
    if(length > 1){
        nodes = realloc(nodes, length * sizeof(struct node *));
        if(nodes == NULL){
            mallocError("node.c", 2);
        }
        return nodes;
    }else{
        fprintf(stderr, "This file does not contain enough symbols to encode\n"); 
        exit(1); //should this be -1 and if so why?
    }
}