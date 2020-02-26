// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include "GPRO-FW-3000/foo.h"
#include "GPRO-FW-3000/random.h"
#include "GPRO-FW-3000/inputoutput.h"
//#define CHEAT
#define NUM_TRIES 3
int main()
{
	printOutStringToConsole("Welcome to the guessing game\n");//print out intro message
	int wouldLikeToPlayAgain = 0;
	do
	{
		int randomNumber = getRandomNumberInRange(0, 10); //generate random number
#ifdef CHEAT	
		printf("\n%d\n", randomNumber);
#endif

		int numTries = NUM_TRIES;
		int hasWon = 0;
		while (!hasWon && numTries != 0)
		{
			printOutStringToConsole("You have ");
			printIntegerToConsole(numTries);
			printOutStringToConsole(" tries remaining. ");
			printOutStringToConsole("Enter a guess value:\n"); //prompt the user for an input
			int guess = getIntegerFromConsole(); // Read in the user entered value
			
           //determine if the input is higher or lower or matching the random num
			if (guess > randomNumber)  //if higher print out that
			{
				printOutStringToConsole("Number is too high\n");
			}
			else if (guess < randomNumber) // if lower print that out
			{
				printOutStringToConsole("Number is too is low\n");
			}
			else if (guess == randomNumber) //if matching win game
			{
				printOutStringToConsole("You win!\n");
				hasWon = 1;
			}
			if (hasWon != 1)
			{
				numTries--;
					if (numTries == 0)
					{
						printOutStringToConsole("You lose, the number was: ");
						printIntegerToConsole(randomNumber);
						printOutStringToConsole("\n");
				}
			}
		}
		printOutStringToConsole("Enter 1 if you would like to play again, 0 if you would like to quit\n");
		wouldLikeToPlayAgain = getIntegerFromConsole(); 
	} while (wouldLikeToPlayAgain); //on finish prompt to play again
}
