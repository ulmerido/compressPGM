#include "Q6.h"
#define MOST_SIGNIFICANT_ON  128 /*10000000*/
#define BYTESIZE 8
#define FORMULAQ6(pixel,expendSize,max_grat_level) (pixel >>= expendSize) * 255 / max_gray_level
#define MASK(pixel,moveBits) (pixel & MOST_SIGNIFICANT_ON)>>moveBits
#define MAX_LEVEL_OF_PGM 255


void convertCompressedImageToPGM(char *compressed_file_name, char* pgm_file_name)
{
	FILE *fp1, *fp2;
	unsigned int i, j, k;
	unsigned char max_gray_level, pixelRead, pixelPrint=0, LogicMask, expendSize;
	unsigned short rows, cols;
	unsigned char countBitIndex = 0;


	fp1 = fopen(compressed_file_name, "rb");

	fp2 = fopen(pgm_file_name, "w");

	if (fp1 == NULL || fp2==NULL)
	{
		printf("\n\t\tERROR - 404 File Name Not Found!\n");
		exit(EXIT_FAILURE);
	}

	fread(&cols, sizeof(unsigned short), 1, fp1);
	fread(&rows, sizeof(unsigned short), 1, fp1);
	fread(&max_gray_level, sizeof(unsigned char), 1, fp1);

	fprintf(fp2, "%s\n%hu %hu\n%hu\n ","P2",cols,rows,MAX_LEVEL_OF_PGM);/*read values of cols, rows*/
	expendSize = expSize(max_gray_level);

	for (i = 0; i < rows;i++)
	{
		for (j = 0; j < cols; )
		{
			fread(&pixelRead, sizeof(unsigned char), 1, fp1);
			for (k = 0; k < (BYTESIZE); k++)                           /*loop that goes on every bit of th byte*/
			{
				LogicMask = MASK(pixelRead, countBitIndex);/*using mask to extract most seg bit from pixelRead, and moving it the the place were we need to add to the pixelprint*/
				pixelPrint = (LogicMask | pixelPrint);
				pixelRead <<= 1;
				countBitIndex++;
				if (countBitIndex == BYTESIZE- expendSize)            /*if we filled the prinPixel with what we need, then we will reverse it to the original pixel by an opposite forula from q5 and add it to the file, rest the data*/
				{
					pixelPrint = FORMULAQ6(pixelPrint, expendSize, max_gray_level);
					fprintf(fp2, "%d ", pixelPrint);
					j++;
					pixelPrint = countBitIndex = 0;
				}

			}

		}
		fwrite("\n", sizeof(unsigned char), 1, fp2);
	}

	fclose(fp1);

	if (countBitIndex !=0)
	{
		pixelPrint = FORMULAQ6(pixelPrint, expendSize, max_gray_level);
		fprintf(fp2, "%d\n", pixelPrint);
	}
	fclose(fp2);


}

unsigned char expSize(unsigned char level)/**/
{

  return(8-(log(level) / log(2)));
}


