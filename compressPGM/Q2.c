//////////////////////////////
#include "Q2.h"

Segment findSingleSegment(grayImage *img, imgPos start, unsigned char threshold )
{
    Segment *res;

    unsigned char **poss;
    unsigned char originalRoot;
    unsigned short x,y;

    x=start[0];
    y=start[1];

   originalRoot=(img->pixels)[x][y];								/*save the value of the root pf withc wi will check the threshold*/
   poss=CreateSegmentPossibilities(img->rows,img->cols);			/*create a matrix that will tell us if a coord in img->pixsels was all ready add to the tree*/

   res = findCoords(img ,poss ,originalRoot ,threshold ,start );	/*function that will return The tree we want */

   freeMatrix(poss, img->rows);

    return *res;
}

Segment *findCoords(grayImage *img, unsigned char **segmentPossibilities, unsigned char originalRoot, unsigned char threshold, imgPos start)
{
	/*the tree will be built branch, by branch of the root.*/
    unsigned short x,y;
	int i, j, rows, cols;
	unsigned char **matrix;
	rows = img->rows;
	cols = img->cols;
	matrix = img->pixels;
    Segment *res;
    treeNode *root;
    treeNodeListCell *currT,*prevT;
    imgPos coords;



	currT = prevT = NULL;                           /*pointrs for the tree we will create*/
    root=(treeNode*)malloc(sizeof(treeNode));     /*create the root and enter the data to him*/
	checkMemoryAllocation(root);
	x=start[0];                                 /*extract coords of root*/
    y=start[1];
    root->position[0]=x;                          /*enter the coords to the root we created*/
	root->position[1] = y;

    root->next_possible_positions=NULL;

    prevT->node=root;

    segmentPossibilities[x][y]=USED;                 /*flag root value from matrix of poss- we finished with him*/


	for (i = x - 1; i<x + 2; i++)                    /*goes on the root neighbors and add the "Special" ones to Tree t*/
	{
		if (i >= 0 && i<rows)
			for (j = y - 1; j<y + 2; j++)
			{
				if (j >= 0 && j<cols)
					if (segmentPossibilities[i][j] != USED)
						if (abs(matrix[i][j] - originalRoot) <= threshold)									/*if the sagments are close values*/
						{
							currT = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));					/*create a new treeNode*/
							checkMemoryAllocation(currT);
							prevT->next = currT;
							prevT = currT;
							coords[0] = i;																	/*extract the coords for the new Nieghbor*/
							coords[1] = j;

							res = findCoords(img, segmentPossibilities, originalRoot, threshold, coords);    /*get segment of neighbor by rec*/
							currT->node = res->root;															/*the List not of our Root get the Segment of the neighbor*/
							free(res);
							segmentPossibilities[i][j] = USED;												/*Flag this neihbor, we saved his data, we dont want hin on the matrix of  p00s */
						}

			}
	}


	if(currT!=NULL)													/*make sure we closed the end of the list*/
    currT->next=NULL;

    res=(Segment*)malloc(sizeof(Segment));							/*create the segment and enter the root to him*/
	checkMemoryAllocation(res);
	res->root=root;													/*connect te segment to the root*/

    return res;													    /*return the segment*/

}



unsigned char **CreateSegmentPossibilities(unsigned short rows,unsigned short cols)/*create matrix of flags for segments*/
{
	unsigned char **matrix;
    unsigned short i,j;

    matrix=(unsigned char**)malloc(sizeof(unsigned char*)*rows);
	checkMemoryAllocation(matrix);
    for(i=0;i<rows;i++)
    {
        matrix[i]=(unsigned char*)malloc(sizeof(unsigned char)*cols);
		checkMemoryAllocation(matrix[i]);
          for(j=0;j<cols;j++)
          {
            matrix[i][j]=UNUSED;
          }
    }




    return matrix;
}

