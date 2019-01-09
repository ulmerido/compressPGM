#include "Q5.h"
#define MOST_SIGNIFICANT_ON 128 /*10000000*/
#define Q5FORMULA(p,max_gray_level,shrink) (p*max_gray_level/255)<<shrink
#define BYTESIZE 8
#define RESET 0
#define MASK(pixel,moveBits) (pixel & MOST_SIGNIFICANT_ON)

void saveCompressed(char *file_name, grayImage *image, unsigned char max_gray_level)
{
	unsigned int i, j, k, countBitIndex = RESET;
	unsigned char **matrix = image->pixels;
	unsigned char newPixel, mask,finalPixel= RESET;
	unsigned char shrinkS = shrinkSize(max_gray_level);
	FILE *fp = fopen(file_name, "wb");
	checkFile(fp);
    
    fwrite(&image->cols,sizeof(unsigned short),1,fp);
    fwrite(&image->rows,sizeof(unsigned short),1,fp);
    fwrite(&max_gray_level,sizeof(unsigned char),1,fp);
     printf("\nmax_gray_level %d",max_gray_level);

	for (i = 0; i < (image->rows) ; i++)                                     /*goes on the rows of the matrix*/
	{
		for (j = 0; j < (image->cols) ; j++)                                /*goes on the cols of the matrix*/
		{
			newPixel = (Q5FORMULA(matrix[i][j], max_gray_level,shrinkS));   /*converts a pixel value by the formula that was given*/
			
                            for(k=0;k<(BYTESIZE-shrinkS);k++)                           /*loop that goes on every bit in the byte after shrinking*/
			{
					if (countBitIndex==BYTESIZE)                            /*if the finalPixel is full, print to file and reset*/
					{
                        fwrite(&finalPixel,sizeof(unsigned char),1,fp);
						finalPixel = countBitIndex = RESET;
					}

				mask=(newPixel &MOST_SIGNIFICANT_ON);                          /*create a mask that extract the left bit the new pixel*/
				mask >>= countBitIndex;
				finalPixel = mask|finalPixel;                               /*add the bit to the finalPixel*/
				countBitIndex++;                                            /*move by 1 the counter for the index of the new bit */
				newPixel<<=1;                                          /*move the Pixel 1 left so next time we will extract the right pixel in the MASK function */

			}
		}
				
	}
	if(countBitIndex!=0)/*cheack if we didnt print the last pixel*/
		{
		    fwrite(&finalPixel,sizeof(unsigned char),1,fp);
		}
	fclose(fp);


	return;

}

unsigned char shrinkSize(unsigned char level)/**/
{

return(8-(log(level) / log(2)));
}
