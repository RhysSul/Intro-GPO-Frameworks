#include "GPRO-FW-3000\display.h"
#include <stdlib.h>
#include <iostream>
using namespace std;


void drawBoard(const char* gameBoard, unsigned char WIDTH, unsigned char HEIGHT)
{
	cout << "Printing Board..." << endl;
	for (unsigned char xpos = 0; xpos < WIDTH; ++xpos)
	{
		for (unsigned char ypos = 0; ypos < HEIGHT; ++ypos)
		{
			cout << (gameBoard + ypos * (xpos +1)) << " ";
		}
		cout << endl;
	}
}



void clearScreen()
{
	system("CLS");
}
