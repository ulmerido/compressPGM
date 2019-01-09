#include "main.h"
#define EXIT 'E'
#define OPTION_ONE 1
#define OPTION_TWO 2
#define OPTION_THREE 3
#define OPTION_FOUR 4
#define OPTION_FIVE 5
#define OPTION_SIX 6
#define RESET '0'
#define MAX_NAME_LEN 25




int main()
{
	unsigned char OptionInput;

	printf("	**Arye Alagem and Ido Ulmer Project: 20.6.2017 : Academit Tel Aviv Yafo**\n");

	OptionInput = printMenu();
	optionInputCases(OptionInput);

	return 0;
}

unsigned char printMenu()
{
	int res;
	char ch;
	printf("________________________________________________________________________");
	printf("\nChoose one of the following options:\n\n");
	printf("1. Read an image file in PGM format\n");
	printf("2. Find all segments\n");
	printf("3. Color the segments\n");
	printf("4. Save the colored image in a compressed format\n");
	printf("5. Compress and save the original image in a compressed format\n");
	printf("6. Convert a compressed image to PGM format\n");
	printf("7. Enter 'E' To Exit\n");
	scanf(" %d", &res);
	scanf("%c", &ch);
	if (ch == EXIT)
	{
		puts("Goodby\n\n\t");
		return ch;
	}

	while ((res > OPTION_SIX || res < OPTION_ONE) && res != EXIT)
	{
		scanf(" %d", &res);
		scanf("%c", &ch);
		if (ch == EXIT)
		{
			puts("GoodBye");
			exit(1);
		}
	}
	clearscr();
	//system("cls");
	printf("________________________________________________________________________\n");
	return(res);

}

void optionInputCases(short OptionInput)
{
	char imageFileName[MAX_NAME_LEN], compresed_Image_File_Name[MAX_NAME_LEN], extracted_Image_File_Name[MAX_NAME_LEN], *tmp = NULL, *tmp2 = NULL;
	grayImage *img = NULL, *coloredImg = NULL;
	int allSegmentsArrSize = 0;
	int threshold = 0, max_gray_level = 0;
	imgPosList *segments = NULL;
	reDirect link;

	link.optionDiraction = link.originalCase = RESET;

	while (OptionInput != EXIT)
	{
		switch (OptionInput)
		{

		case OPTION_ONE:

			if (img != NULL)
			{
				printf("Freeing From memory the last image.....");
				freeMatrix(img->pixels, img->rows);
				printf("Freeing Complete\n");
			}

			printf("\n\t\t\tSection One:\ninsert PGM image name:\t");
			scanf(" %s", imageFileName);
			printf("Reading the Image %s...\nPlease Wait, this may take a few secondes\n", imageFileName);
			tmp = addEndingPGM(imageFileName);

			img = readPGM(tmp);
			free(tmp);
			clearscr();
			printf("Reading Complete\n");



			if (link.originalCase == OPTION_TWO || link.originalCase == OPTION_FOUR)
				link.optionDiraction = OPTION_TWO;
			else
				if (link.originalCase == OPTION_FIVE)
					link.optionDiraction = OPTION_FIVE;
				else
					link.optionDiraction = link.originalCase = RESET;
			printf("\nSection One Ended:\n");
			break;





		case OPTION_TWO:

			if (img == NULL)
			{
				printf("No PGM image Was Loaded \nRedirecting to Section One...\n\n");
				printf("_________________________________________________________________________\n");

				link.optionDiraction = OPTION_ONE;
				if (link.originalCase == RESET)
					link.originalCase = OPTION_TWO;
				break;
			}


			printf("\n\t\t\tSection Two:\n");

			if (segments != NULL)
			{
				printf("Freeing the last Segment List...");
				freeList(segments, allSegmentsArrSize);
				printf("Freeing Complite\n");

			}

			printf("\nEnter thresehold for segments: integer between [0,255]:\t");
			scanf(" %d", &threshold);
			clearscr();


			printf("\nThe threshold you enterd: is %d\n", threshold);
			allSegmentsArrSize = findAllSegments(img, threshold, &segments);
			printf("\nArray of Segments with threshold %d was sucsessfully created\nThere are %d diffrent segments in this array\n", threshold, allSegmentsArrSize);




			if (link.originalCase == OPTION_THREE || link.originalCase == OPTION_FOUR)
				link.optionDiraction = OPTION_THREE;
			else
				link.optionDiraction = link.originalCase = RESET;
			printf("\nSection Two Ended:\n");

			break;

		case OPTION_THREE:


			if (segments == NULL)
			{
				printf("\nThere Was No request for finding segments\nRedirecting to Section Two...\n\n");
				printf("_________________________________________________________________________\n");

				link.optionDiraction = OPTION_TWO;
				if (link.originalCase == RESET)
					link.originalCase = OPTION_THREE;
				break;
			}

			printf("\n\t\t\tSection Three :\n");
			if (coloredImg != NULL)
			{
				printf("Freeing the last time Colored img............");
				freeMatrix(coloredImg->pixels, coloredImg->rows);
				printf(" Finished freeing\n");
			}


			printf("Creating colored image...............\n");
			coloredImg = colorSegments(segments, allSegmentsArrSize);
			printf("Finished!\n");

			if (link.originalCase == OPTION_FOUR)
				link.optionDiraction = OPTION_FOUR;
			else
				link.optionDiraction = link.originalCase = RESET;
			printf("Section Three Ended :\n");
			break;

		case OPTION_FOUR:
			printf("\n\t\t\tSection Four :\n");

			if (coloredImg == NULL)
			{
				printf("\nThere Was No Request for finding segments\nRedirecting to Section Three...\n\n");
				printf("________________________________________________________________________\n");

				link.optionDiraction = OPTION_THREE;
				link.originalCase = OPTION_FOUR;
				break;
			}

			printf("\nEnter a name for compresed colored image\n");
			scanf(" %s", compresed_Image_File_Name);
			tmp = addEndingBin(compresed_Image_File_Name);
			printf("Enter max gray color for compration ( color<128 )\n");
			scanf(" %d", &max_gray_level);
			clearscr();

			printf("Creating compresed file with the name :%s. with max gray level of: %d\n", tmp, max_gray_level);
			saveCompressed(tmp, coloredImg, max_gray_level);
			printf("The File Has Been Created!\n");
			free(tmp);

			link.optionDiraction = link.originalCase = RESET;
			printf("\nSection Four Ended :\n");
			break;

		case OPTION_FIVE:
			printf("\n\t\t\tSection Five :\n");

			if (img == NULL)
			{
				printf("\nNo PGM image Was Loaded\nRedirecting to Section One...\n\n");
				printf("________________________________________________________________________\n");

				link.optionDiraction = OPTION_ONE;
				link.originalCase = OPTION_FIVE;
				break;
			}

			printf("\nEnter a name for the compresed image\n");
			scanf(" %s", compresed_Image_File_Name);
			tmp = addEndingBin(compresed_Image_File_Name);
			printf("Enter max gray color for compration ( color<128 )\n");
			scanf(" %d", &max_gray_level);
			clearscr();
			printf("Creating compresed file with the name: %s.\nwith max gray level of: %d\n", tmp, max_gray_level);
			saveCompressed(tmp, img, max_gray_level);
			free(tmp);
			printf("The File Has Been Created!\n");

			link.optionDiraction = link.originalCase = RESET;
			printf("Section Five Ended :\n");
			break;

		case OPTION_SIX:

			printf("\n\t\t\tSection Six :\n");

			printf("\nEnter The name of the compresed image\n");
			scanf(" %s", compresed_Image_File_Name);
			tmp = addEndingBin(compresed_Image_File_Name);

			printf("\nEnter a Name for the Extracted Image\n");
			scanf(" %s", extracted_Image_File_Name);
			tmp2 = addEndingPGM(extracted_Image_File_Name);
			clearscr();
			printf("Converting the Compressed Bin Image %s To PGM by the name of: %s \n", tmp, tmp2);
			convertCompressedImageToPGM(tmp, tmp2);
			printf("The File Has Been Converted!\n");
			free(tmp);
			free(tmp2);
			link.optionDiraction = link.originalCase = RESET;
			printf("Section Six Ended :\n");
			break;


		default:
			return;
			break;
		}
		OptionInput = link.optionDiraction;

		if (link.optionDiraction == RESET)
			OptionInput = printMenu();

	}
}

void freeList(imgPosList *lst, int size)
{
	int i;
	imgPosCell *curr, *prevv;
	for (i = 0; i < size; i++)
	{
		curr = lst[i].head;
		while (curr != NULL)
		{
			prevv = curr;
			curr = curr->next;
			free(prevv);
		}
	}
	free(lst);
}



void clearscr(void)
{
#ifdef _WIN32
	system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
	system("clear");
	//add some other OSes here if needed
#else
#error "OS not supported."
	//you can also throw an exception indicating the function can't be used
#endif
}



char* addEndingBin(char* fileName)
{
	int len;
	char *tmp;
	len = strlen(fileName);
	if (strcmp(fileName + len - 4, ".bin") == 0)
	{
		tmp = (char*)malloc((len + 1) * sizeof(char));
		checkMemoryAllocation(tmp);
		strcpy(tmp, fileName);
		return tmp;
	}

	len = len + 5; // .txt \0 =5 chars
	tmp = (char*)malloc(len * sizeof(char));
	checkMemoryAllocation(tmp);
	strcpy(tmp, fileName);
	strcat(tmp, ".bin");
	return tmp;
}


char* addEndingPGM(char* fileName)
{
	int len;
	char *tmp;
	len = strlen(fileName);
	if (strcmp(fileName + len - 4, ".pgm") == 0)
	{
		tmp = (char*)malloc((len + 1) * sizeof(char));
		checkMemoryAllocation(tmp);
		strcpy(tmp, fileName);
		return tmp;
	}
	len = len + 5; // .txt \0 =5 chars
	tmp = (char*)malloc(len * sizeof(char));
	checkMemoryAllocation(tmp);
	strcpy(tmp, fileName);
	strcat(tmp, ".pgm");
	return tmp;
}
