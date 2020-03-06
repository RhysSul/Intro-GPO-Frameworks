#include <iostream>
#include "GPRO-FW-3000/inputoutput.h"
using namespace std;
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

void promptUserForInteger(const string &message, int& assign)
{
    cout << message << endl;
    cin >> assign;
}