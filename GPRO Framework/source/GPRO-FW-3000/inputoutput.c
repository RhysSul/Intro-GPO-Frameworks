#include <stdio.h>
#include "GPRO-FW-3000/inputoutput.h"
void printOutStringToConsole(char* outputMessage)
{
	printf(outputMessage);
}

int getIntegerFromConsole()
{
    int num, nitems;
    nitems = scanf_s("%d", &num);
    return num;
}

void printIntegerToConsole(int intToPrint)
{
    printf("%d", intToPrint);
}