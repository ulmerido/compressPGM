#include "Q6.h"

unsigned char printMenu();
void freeList(imgPosList *lst, int size);
void optionInputCases(short OptionInput);
void clearscr(void);
char* addEndingBin(char* fileName);
char* addEndingPGM(char* fileName);

typedef struct _redirect {

	unsigned char optionDiraction;

	unsigned char originalCase;

}reDirect;
