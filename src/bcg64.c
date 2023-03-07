#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a struct to keep frequency and binary code representation of a character
typedef struct code{
  unsigned int freq;
  char *binary_code;
} Code;

typedef struct Node{
  char c;
  int freq;
  struct Node *left, *right;
} Node;

typedef struct minheap{
  int size;
  int capacity;
  Node** array;
} minHeap;

Node* initalizeNode(char letter, int freq, struct Node* left, struct Node* right){
  Node* newNode = malloc(sizeof(Node));
  newNode->c = letter;
  newNode->freq = freq;
  newNode->left = left;
  newNode->right = right;
  
  return newNode;
}

minHeap* initalizeMinHeap(int capacity){
  minHeap* newHeap = malloc(sizeof(minHeap));
  newHeap->size = 0;
  newHeap->capacity = capacity;
  newHeap->array = malloc(sizeof(Node) * capacity);
  return newHeap;
}

void freeNode(Node* node){
  free(node);
}

int isLeaf(Node* node){
  return !((node->left) || (node->right));
}

void freeMinHeap(minHeap* MH){
  for(int i = 0 ; i < MH->capacity; i++){
    freeNode(MH->array[i]);
  }
  free(MH->array);
  free(MH);
}

void freeTreeNode(Node* root){
  if(isLeaf(root)){
    freeNode(root);
  }else{
    freeTreeNode(root->left);
    freeTreeNode(root->right);
    freeNode(root);
  }
  
}

void swapNodes(minHeap* MH, int a, int b){
  Node* temp = MH->array[a];
  MH->array[a] = MH->array[b];
  MH->array[b] = temp;
}

void upHeap(minHeap* MH, int index){
  if(index == 0){
      return; //node is the root
  }
  int parentIndex = (int)((index-1)/2);
  if(MH->array[parentIndex]->freq <= MH->array[index]->freq){
    return; //bigger than parent, already deeper in minHeap
  }
  // swapNodes(MH->array[parentIndex], MH->array[index]);
  swapNodes(MH, parentIndex, index);
  upHeap(MH, parentIndex);
}

void insertIntoMinHeap(minHeap* MH, Node* newNode){
  MH->array[MH->size] = newNode;
  upHeap(MH, MH->size);
  MH->size++;
}

Node* insertCodesIntotree(Code** codes, Node* root, Node* newNode, int codeIndex){
  if(root == NULL){
    root = initalizeNode('0', 0, NULL, NULL);
  }
  if(codeIndex < strlen(codes[newNode->c]->binary_code)){
    root->freq += newNode->freq;
    if(codes[newNode->c]->binary_code[codeIndex] == '0'){
      root->left = insertCodesIntotree(codes, root->left, newNode, ++codeIndex);
    }else{
      root->right = insertCodesIntotree(codes, root->right, newNode, ++codeIndex);
    }
  }else{
    if(codes[newNode->c]->binary_code[codeIndex-1] == '0'){
      root->left = newNode;  
      return root->left;
    }else{
      root->right = newNode;  
      return root->right;
    }
  }
  return root;

}


int minChildIndex(minHeap* MH, int index){
  if(MH->size-1 >= (index+1) *2){
    if(MH->array[(index+1)*2] > MH->array[(index+1)*2-1]){
      return (index+1)*2-1;
    }else{
      return (index+1)*2;
    }
  }else if(MH->size -1 == ((index+1) *2 -1)){
    return ((index+1) * 2 -1);
  }else{ //why do I need this else statement in slide code?
    return -1;
  }
}

void downHeap(minHeap* MH, int index){
  if(MH->size-1 < ((index+1) * 2 -1)){
    return; // no children
  }
  int minimumChildIndex = minChildIndex(MH, index);
  if(MH->array[index]->freq <= MH->array[minimumChildIndex]->freq){
    return; //parent smaller than child
  }
  // swapNodes(MH->array[index], MH->array[minimumChildIndex]);
  swapNodes(MH, index, minimumChildIndex);
  downHeap(MH, minimumChildIndex);

}

Node* extractMin(minHeap* MH){
  if(MH->size > 0){
    return MH->array[0];
  }else{
    return NULL;
  }
}

void deleteMin(minHeap* MH){
  // swapNodes(MH->array[0], MH->array[MH->size-1]);
  swapNodes(MH, 0, MH->size-1);
  MH->size--;
  downHeap(MH, 0);
}

void initalizeHuffmanTree(minHeap* MH){
  while(MH->size >= 2){
    Node* left = extractMin(MH);
    deleteMin(MH);
    Node* right = extractMin(MH);
    deleteMin(MH);
    Node* newNode = initalizeNode('0', left->freq + right->freq, left, right);
    insertIntoMinHeap(MH, newNode);
  }
}

void printHeap(Node *myNode) {
    printf("[ %c : %d ]", myNode->c , myNode->freq);
    printf("\t");

    if(myNode->left != NULL){
      printHeap(myNode->left);
    }else{
      printf("[ NULL ]");
    }

    if(myNode->right != NULL){
      printHeap(myNode->right);
    }else{
      printf("[ NULL ] ");
    }

    printf("\n");
}

void HuffmanCodes(Node* root, char* currCode, Code** codes){
  // printf("%s", currCode);
  // printf("[ %c : %d ]", root->c , root->freq);
  // printf("%d\n\n", isLeaf(root));

  if(isLeaf(root)){
    codes[root->c]->binary_code = malloc(sizeof(char) * (strlen(currCode)+1));
    strcpy(codes[root->c]->binary_code, currCode);
  }

  char* currCodeStr = malloc(sizeof(char) * (strlen(currCode)+1));

  if(root->left != NULL){
    strcpy(currCodeStr, currCode);
    strcat(currCodeStr, "0");
    HuffmanCodes(root->left, currCodeStr, codes);
  }

  if(root->right != NULL){
    strcpy(currCodeStr, currCode);
    strcat(currCodeStr, "1");
    HuffmanCodes(root->right, currCodeStr, codes);
  }
  free(currCodeStr);
}

int main(int argc, char **argv)
{
    char* action = argv[1]; // will be "encode" or "decode" signifying the mode of the program
    
    char* inputTextFilePath;
    char* codeTableFilePath;
    char* outputEncoded;

    char* inputTable;
    char* inputEncoded;
    char* outputDecoded;

    if( strcmp(action, "encode") == 0){
      // //for encode mode
      char* inputTextFilePath = argv[2]; // will be the path to input text file
      char* codeTableFilePath = argv[3]; // will be the path to output code table file
      char* outputEncoded = argv[4]; // will be the path to output encoded text file
      /*----------------ENCODER-----------------------*/
      /*----------------------------------------------*/
      /*To read the input text file, you might want to use a code as follows*/
        FILE *inputFile = fopen(inputTextFilePath, "r");
        if (inputFile == NULL)
        {
          printf("Could not open file to read: %s\n",inputTextFilePath);
          return 1;
        }

      // initialize the code table, which will store the frequency of each character,
      // and eventually the binary code. We are allocating a space of 256 in the
      // table, and the character's ASCII code will serve as hashing the index for
      // that character.
      Code **codeTable = malloc(sizeof(Code)*256);

      //set counters to zero initially
      for(int i = 0; i < 256; i++){
        codeTable[i] = malloc(sizeof(Code));
        codeTable[i]->freq = 0;
      }

      int totalUniqueCharacters=0;
      int totalNumOfCharacters=0;
      char c;
        //read the file character by character
        while ((c = fgetc(inputFile)) != EOF && c!='\n')
        {
          //increase the frequency of the character by one
        if(codeTable[c]->freq == 0){
        totalUniqueCharacters++; 
        }
        codeTable[c]->freq++;
        //increase the total character count
        totalNumOfCharacters++;
        }
        fclose(inputFile);
        
        minHeap* MH = initalizeMinHeap(totalUniqueCharacters);
        
        for(int i = 0 ; i < 256; i++){
          if(codeTable[i]->freq != 0){
            Node* newNode = initalizeNode((char)(i), codeTable[i]->freq, NULL, NULL);
            insertIntoMinHeap(MH, newNode);
          }
        }

        // for(int i = 0 ; i < MH->size; i++){
        //   printf("[ %c : %d ]", MH->array[i]->c , MH->array[i]->freq);
        // }
        // printf("\n");

        char* currCode = "";
        initalizeHuffmanTree(MH);

        HuffmanCodes(extractMin(MH), currCode, codeTable);

        // printHeap(MH->array[0]);
        
        //now that you have collected the frequency of each character that is present 
        //in the input file, you need to generate the code table.
        
        // Hint: when initializing the heap to be used in the generation of Huffman
        // 		 tree, keep in mind that you know how many unique characters have
        //		 appeared in the input text. You can get this number by going through
        //		 your codeTable...
        
        /*----------------------------------------------*/
        //to write the code table into the file, you might want to use a code as follows
        FILE *codeTableFile = fopen(codeTableFilePath, "w");
        if (codeTableFile == NULL)
        {
            printf("Could not open file to write: %s\n",codeTableFilePath);
            return 1;
        }

        // Write the code table into file:
        for(int i = 256 - 1; i >= 0; i--)
        {
           if(codeTable[i]->freq != 0){
            fprintf(codeTableFile, "%c\t%s\t%d\n", (char)(i), codeTable[i]->binary_code, codeTable[i]->freq);
          }
        }
        fclose(codeTableFile);
        
        unsigned int uncompressed =  totalNumOfCharacters;
        unsigned int compressed_size =  0;

        FILE *outputEncodedFile = fopen(outputEncoded, "w");
        if (outputEncodedFile == NULL)
        {
            printf("Could not open file to write: %s\n",outputEncoded);
            return 1;
        }

        inputFile = fopen(inputTextFilePath, "r");
        while ((c = fgetc(inputFile)) != EOF && c!='\n')
        { //prints out the encoded string and does the compression math
          compressed_size += strlen(codeTable[c]->binary_code);
          fprintf(outputEncodedFile, "%s", codeTable[c]->binary_code);
        }
        fclose(inputFile);
        fclose(outputEncodedFile);

        /*----------------------------------------------*/
        //To print the statistics about the compression, use print statements as follows
        printf("Original: %d bits\n", uncompressed*8); //assuming that you store the number of characters in variable "uncompressed". *8 is because ASCII table uses 8 bits to represent each character
        printf("Compressed: %d bits\n", compressed_size); //assuming that you store the number of bits (i.e., 0/1s) of encoded text in variable "compressed_size"
        printf("Compression Ratio: %.2f%%\n", (float)compressed_size/((float)uncompressed*8)*100); //This line will print the compression ration in percentages, up to 2 decimals.
        

        /*----------------------------------------------*/
        //to write encoded version of the text in 0/1 form into text file, you can use a code similar to fprintf statment above that is suggested for writing code table to the file.


      for(int i = 0 ; i < 256; i++){
        free(codeTable[i]->binary_code); //why cant i free code
        free(codeTable[i]);
      }
      free(codeTable);

      freeMinHeap(MH);

    }else{
          /*----------------DECODER-----------------------*/
          /*----------------------------------------------*/
          //When decoding, you will need to:
          //1) read code table: you can use fscanf() function, since the code table file is well structured. Alternatively, you can also use the read statements from above as was used for reading input text file.
          //2) read encoded text, which is a single line consisting of 0/1 characters: This file is better be read character by character, for which you can use a code similar to getc() code above
          //3) write the decoded text into file: for that, you can write it into the file using a code similar to fprintf() usages exemplified above.
          
          //for decode mode
          char* inputTable = argv[2]; // will be the path to input code table file
          char* inputEncoded = argv[3]; // will be the path to input encoded text file
          char* outputDecoded = argv[4]; // will be the path to output decoded text file
          
    
         

          FILE *inputTableFile = fopen(inputTable, "r");
          if (inputTableFile == NULL)
          {
              printf("Could not open file to write: %s\n", inputTable);
              return 1;
          }

          char c;
          char binary_code_val[8];
          int frequency;
          // Write the code table into file:
          
          Node* root = NULL;
          Code **codeTable = malloc(sizeof(Code)*256);
          //set counters to zero initially
          for(int i = 0; i < 256; i++){
            codeTable[i] = malloc(sizeof(Code));
          }

          while (fscanf(inputTableFile, "%c\t%s\t%d\n", &c, binary_code_val, &frequency) != EOF)
          {
            int len = strlen(binary_code_val);
            if(c == '1' || c == '0'){   
              memmove(binary_code_val+1, binary_code_val, ++len);
              *binary_code_val = c;
              c = ' ';
            }

            // printf("___,%c,%s,%d __", c, &binary_code_val, frequency);

            codeTable[c] = malloc(sizeof(Code));
            codeTable[c]->freq = frequency;
            codeTable[c]->binary_code = malloc(sizeof(char) * (strlen(binary_code_val) + 1));
            strcpy(codeTable[c]->binary_code, binary_code_val);
            root = insertCodesIntotree(codeTable, root, initalizeNode((char)(c), frequency, NULL, NULL), 0);
          }
          fclose(inputTableFile);

          //build tree
          // printHeap(root);

          //read in the ecnoded string sequence and decode it
          FILE *inputEncodedFile = fopen(inputEncoded, "r");
          if (inputEncodedFile == NULL)
          {
              printf("Could not open file to write: %s\n",inputEncoded);
              return 1;
          }
          Node* currNode = root;
          FILE *outputDecodedFile = fopen(outputDecoded, "w");
          if (outputDecodedFile == NULL)
          {
              printf("Could not open file to write: %s\n",outputDecoded);
              return 1;
          }
          while ((c = fgetc(inputEncodedFile)) != EOF && c!='\n')
          {
            // printf(" currDigit: %c - %d | ", c, currNode->freq);

            if(isLeaf(currNode)){
              // printf("%c", currNode->c);
              fprintf(outputDecodedFile, "%c", currNode->c);
              if(c == '0'){
                currNode = root->left;
              }else{
                currNode = root->right;
              }
            }else{
              if(c == '0'){
                currNode = currNode->left;
              }else{
                currNode = currNode->right;
              }
            }
          }
          if(isLeaf(currNode)){
              // printf("%c", currNode->c);
              fprintf(outputDecodedFile, "%c", currNode->c);
          }
    
    for(int i = 0 ; i < 256; i++){
        free(codeTable[i]->binary_code); //why cant i free code
        free(codeTable[i]);
    }
      free(codeTable);

      freeTreeNode(root);
      freeNode(currNode);
      freeNode(root);

    }

}
