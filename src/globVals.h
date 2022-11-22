#ifndef GLOBAL
#define GLOBAL

#define ASCII 256

struct node {
    unsigned char token;
    int freq;
    struct node *left;
    struct node *right;
};

struct heap {
    struct node **array;
    int size;
};
extern int codeLength;
extern int length;
extern int fileSize;

extern FILE *inp;
extern FILE *out;

extern void mallocError(char *filename, int num);
extern void ccloseAll(void);

#endif