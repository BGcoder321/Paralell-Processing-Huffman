#ifndef HEAP
#define HEAP

extern struct heap *makeHeap(void);
extern void freeHeap(struct heap *heap);

extern void insert(struct heap *heap, struct node *node);
extern struct node *removeMin(struct heap *heap);

#endif