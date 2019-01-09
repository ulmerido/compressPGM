#include "Q1.h"
#define USED 0
#define UNUSED 1

Segment findSingleSegment(grayImage *img, imgPos start, unsigned char threshold );
Segment *findCoords(grayImage *img, unsigned char **segmentPossibilities, unsigned char originalRoot, unsigned char threshold, imgPos start);
unsigned char **CreateSegmentPossibilities(unsigned short rows,unsigned short cols);
