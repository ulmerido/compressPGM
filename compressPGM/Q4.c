#include "Q4.h"
#define MAX(a,b)  ((a)>(b)) ? (a):(b) /*Macro MAX*/
#define Q4FORMOLA(i,size)	(i*255)/(size-1) /*forumla of Q4*/
#define BLACK 0
#define MIN_SIZE_FOR_FORMULA 2
grayImage *colorSegments(imgPosList*segments, unsigned int size)
{
	unsigned int i, x, y;
	unsigned short rows, cols;
	unsigned char **matrix;
	imgPosCell *curr;
	grayImage *res = (grayImage*)malloc(sizeof(grayImage) * 1);

	findMaxRowCol(segments, size, &rows, &cols); /*Find The max Row and Col so we will create the matrix in the correct size*/

	matrix = CreateUSCharMatrix(rows, cols);
	for (i = 0; i < size; i++)/*color the segments by the formula givin*/
	{
		curr = segments[i].head;
		while (curr != NULL)
		{
			x = curr->position[0];
			y = curr->position[1];
			if (size >=  MIN_SIZE_FOR_FORMULA)                            /*if the size is 1 we cant use the formula (dividing by 0)*/
				matrix[x][y] = Q4FORMOLA(i, size);
			else
		    matrix[x][y] = BLACK;  /*color it in black*/
			curr = curr->next;
			
		}
	}

	res->pixels = matrix;
	res->cols = cols;
	res->rows = rows;

	return res;

}

void findMaxRowCol(imgPosList*segments, unsigned int size, unsigned short *row, unsigned short *col)/*find max of (x,y) in ImgPos List where x= row and y = col*/
{
	unsigned int i;
	unsigned short currRow, currCol;
	imgPosCell *curr;
	*row = 0;
	*col = 0;
	for (i = 0; i < size; i++)
	{
		curr = segments[i].head;
		while (curr != NULL)
		{
			currRow = curr->position[0];
			currCol = curr->position[1];
			curr = curr->next;
			*row = MAX(currRow, *row);
			*col = MAX(currCol, *col);

		}

	}
	*row = *row + 1;
	*col = *col + 1;

	return;

}