#ifndef _Q1
#define _Q1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

//////////////////////////////////////
typedef struct _grayImage{

unsigned short rows, cols;

unsigned char **pixels;

}grayImage;

typedef unsigned short imgPos[2];

///////////////////////////////////////

typedef struct _treeNode{

imgPos position;

struct _treeNodeListCell *next_possible_positions;

}treeNode;

/////////////////////////////////////

typedef struct _treeNodeListCell {

treeNode *node;

struct _treeNodeListCell *next;

}treeNodeListCell;
//////////////////////////////////////



typedef struct _segment{

treeNode *root;

}Segment;
////////////////////////////////////


grayImage *readPGM(char *fname);
long int fileSize(FILE *file);
unsigned char **CreateUSCharMatrix( unsigned short N,  unsigned short M);
void checkMemoryAllocation(void *ptr);
void freeMatrix(unsigned char **ptr, int rows);
void checkFile(FILE* ptr);




#endif //_Q1
