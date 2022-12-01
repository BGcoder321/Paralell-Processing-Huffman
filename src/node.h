#ifndef NODE
#define NODE

extern struct node *makeNode(unsigned char token, int freq, struct node *left, struct node *right);
extern struct node **makeNode(int *vals);

#endif