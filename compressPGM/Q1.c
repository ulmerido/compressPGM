//////////////////////////////
#include "Q1.h"
grayImage *readPGM(char *fname)/*Q1 function*/
{
    FILE *fp1;
	unsigned short N, M, maxGray, i, j, cols, rows;
    unsigned char **matrix;
	char dummy;
    unsigned char data;
    long int fSize;
    grayImage *res;

    res=(grayImage*)malloc(sizeof(grayImage)*1);/*create the img*/

    fp1=fopen(fname,"rt");/*open the txt file*/
	checkFile(fp1);
    fSize=fileSize(fp1);
    while(1)               /*skip first line*/
    {
        dummy=fgetc(fp1);
        if(dummy=='\n')
            break;
    }
    fscanf(fp1,"%hu %hu %hu",&N,&M,&maxGray);/*read values of cols, rows*/
    cols=N;
    rows=M;

    matrix=CreateUSCharMatrix(rows,cols);/*create the matrix*/

    i=j=0;/**/
    while(ftell(fp1)<fSize)                                           /*fill Matrix Data from txt*/
    {
        fscanf(fp1,"%hhu",&data);
        matrix[i][j]=data;
        j++;
        if((i+1)*(j)==cols*rows)                                    /*end of matrix*/
            break;

        if(j==cols)                                                  /*New Line*/
        {
            j=0;
            i++;
        }
    }

    res->pixels=matrix;
    res->cols=cols;
    res->rows=rows;

    fclose(fp1);
	

    return res;

}

long int fileSize(FILE *file)/*return file size*/
{

    int res;
	fseek(file, 0, SEEK_END);
	res = ftell(file);
	fseek(file, 0, SEEK_SET);

	return res;
}

unsigned char **CreateUSCharMatrix( unsigned short N,  unsigned short M)/*create unsigned char matrix*/
{
    int i;
    unsigned char** matrix;

    matrix=(unsigned char**)malloc(sizeof(unsigned char*)*N);          /* Create Matrix*/

    for(i=0;i<N;i++)
    {
      matrix[i]=(unsigned char*)malloc(sizeof(unsigned char)*M);
    }

    return matrix;
}



void freeMatrix(unsigned char **ptr, int rows)/*free a matrix*/
{
	int i;

	for (i = 0; i < rows; i++)
		free(ptr[i]);
	free(ptr);
}


void checkMemoryAllocation(void *ptr)/*check memory allocation*/
{
	if (ptr == NULL)
	{
		puts("A memory allocation error has been detected");
		exit(1);
	}
}

void checkFile(FILE  *ptr)
{
	if (ptr == NULL)
	{
		printf("\n\t\tERROR - 404 File Name Not Found!\n");
		exit(EXIT_FAILURE);
	}
}
