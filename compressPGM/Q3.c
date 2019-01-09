#include "Q3.h"


void AddimgPosCellToEndOfList(imgPosList *lst) /*adding data to end of a list*/
{
	imgPosCell *res;
	res = (imgPosCell*)malloc(sizeof(imgPosCell));
	checkMemoryAllocation(res);
	res->next = NULL;

	if (lst->tail == NULL)
	{
		lst->tail = lst->head = res;
		res->next = res->prev = NULL;
		return;
	}

	lst->tail->next = res;
	res->prev = lst->tail;
	lst->tail = res;

	return;

}

int findAllSegments(grayImage *img, unsigned char threshold, imgPosList **segments) /*finding segments for every pixel*/
{
	unsigned char **matrixFlag;
	int i, j;
	int Psize = 1, index = 0;
	imgPos start;
	imgPosList *res;
	res = (imgPosList*)malloc(sizeof(imgPosList)*Psize);
	checkMemoryAllocation(res);
	matrixFlag = CreateSegmentPossibilities(img->rows, img->cols); /*matrix of flags*/

	for (i = 0; i < img->rows; i++)
	{
		
		for (j = 0; j < img->cols; j++)
		{
			
			if (matrixFlag[i][j] == UNUSED)
			{
				if (index == Psize)             /*realloc if we need more space in the array*/
				{
					Psize *= 2;
					res = (imgPosList*)realloc(res, Psize * sizeof(imgPosList));
					checkMemoryAllocation(res);
				}
				start[0] = i;
				start[1] = j;
				res[index].head = res[index].tail = NULL;

				matrixFlag[i][j] = USED;/*flag this coord*/
				AddimgPosCellToEndOfList(&res[index]);/*add the coord to the list*/
				res[index].tail->position[0] = i;
				res[index].tail->position[1] = j;



				ListOfASegment(img, matrixFlag, &threshold, &img->pixels[i][j], &start, &res[index]); /*finding his segments*/
				index++;
			}
			
		}
	}
	res = (imgPosList*)realloc(res, index * sizeof(imgPosList));
	checkMemoryAllocation(res);
	freeMatrix(matrixFlag, img->rows);
	*segments = res;
	return index;


}


void ListOfASegment(grayImage *img, unsigned char **matrixFlag, unsigned char *threshold, unsigned char *originalRoot, imgPos *start, imgPosList *lst)
{

	int i, j, k, l, count=0;
	imgPosCell *curr, *saveHead;

	for (i = (*start)[0] - 1; i<(*start)[0] + 2; i++)                        /*goes on the root neighbors and add to list the ones we will want to tie*/
	{
		if (i >= 0 && i<img->rows)
			for (j = (*start)[1] - 1; j<(*start)[1] + 2; j++)
			{
				if (j >= 0 && j<img->cols)
					if ((abs(img->pixels[i][j] - *originalRoot) <= *threshold) && (matrixFlag[i][j] == UNUSED))  /*if the sagments are close values*/
					{
						k = j;											/* in the nex 2 whiles we will go on every row down and colom right to the pixel[i][j], we will check if he should be on the list, we will stop on the 1st one that shouldnt be there*/
																		
																		/*   111XXXXX
																			 110XXX11
																			 11XXX11X
																			 1111X111

																			 if pixel[i][j] is 0 in the matrix above;
																			 and X is a value that is in the threshold of the root
																			 in the end of this loop we will add all of the fllowing V to the list(and 0)
																			 111XXXXX
																			 110VVV11
																			 11VVV11X
																			 1111V111
																		*/
						while ((k<img->cols) && (abs(img->pixels[i][k] - *originalRoot) <= *threshold) && (matrixFlag[i][k] == UNUSED))
						{
							l = i;
							while ((l<img->rows) && (abs(img->pixels[l][k] - *originalRoot) <= *threshold) && (matrixFlag[l][k] == UNUSED))
							{

								matrixFlag[l][k] = USED;			/*flag this coord*/
								AddimgPosCellToEndOfList(lst);		/*add the coord to the list*/
								lst->tail->position[0] = l;
								lst->tail->position[1] = k;
								count++;                           /*counting how many we add to the list*/
								l++;
							}
							k++;
						}

					}
			}
	}

	saveHead = curr = lst->head;/* in the nex part we will go on every coord of the list (exept the 1st one) and send it recursevly to add there nigebros that are int the roots threshold*/

	if (curr != NULL)
		curr = curr->next;

	for (i = 0; i<count; i++)/*goes on every pos we add to the list - ONLY from the ones above*/
	{
		lst->head = lst->tail;/*we send only the tail, so in the next rec call we wont check the coords of this call */
		ListOfASegment(img, matrixFlag, threshold, originalRoot, &curr->position, lst);  //send the list by rec
		curr = curr->next;
	}

	lst->head = saveHead;/*restore the head*/

}
