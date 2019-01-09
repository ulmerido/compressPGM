#include "Q2.h"
typedef struct _imgPosCell {

	imgPos position;

	struct _imgPosCell *next, *prev;

}imgPosCell;

typedef struct _imgPosList {

	imgPosCell *head;

	imgPosCell *tail;

}imgPosList;



void AddimgPosCellToEndOfList(imgPosList *lst);

int findAllSegments(grayImage *img, unsigned char threshold, imgPosList **segments);
void ListOfASegment(grayImage *img, unsigned char **matrixFlag, unsigned char *threshold, unsigned char *originalRoot, imgPos *start, imgPosList *lst);
