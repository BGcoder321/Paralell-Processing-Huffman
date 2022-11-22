#include <stdio.h>
#include <stdlib.h>

#include <globVals.h>

int codeLength = 0;
int length = 0;
int fileSize = 0;

FILE *inp = NULL;
FILE *out = NULL;

void mallocError(char *filename, int num){ 
    fprintf(stderr, "Could not allocate memory ($s, $d)\n", filename, num);
    exit(-1);
}

void closeAll(void){
    if(inp != NULL){    
        fclose(inp);
    }
    if(out != NULL){
        fclose(out);
    }
}