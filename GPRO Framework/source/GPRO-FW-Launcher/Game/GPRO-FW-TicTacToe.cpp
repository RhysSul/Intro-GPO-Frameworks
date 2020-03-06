
#include <stdio.h>

#include <iostream>
using namespace std;
//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_TICTACTOE_PLAYERS					2
#define GS_TICTACTOE_BOARD_WIDTH				3
#define GS_TICTACTOE_BOARD_HEIGHT				3

enum gs_tictactoe_space_state
{
	// invalid space state
	gs_tictactoe_space_invalid = -1,

	// states visible to both players
	gs_tictactoe_space_open,	// space is open
	gs_tictactoe_space_o,		// space is taken by O player
	gs_tictactoe_space_x,		// space is taken by X player
};
#ifndef __cplusplus
typedef		enum gs_tictactoe_space_state		gs_tictactoe_space_state;
#endif	// !__cplusplus

// tic-tac-toe game state
typedef		unsigned char						gs_tictactoe_index;
typedef		gs_tictactoe_space_state			gs_tictactoe[GS_TICTACTOE_BOARD_WIDTH][GS_TICTACTOE_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,w,h)			(x < w && y < h)
#define GS_TICTACTOE_VALID(x,y)					GS_VALIDATE_COORDINATE(x,y,GS_TICTACTOE_BOARD_WIDTH,GS_TICTACTOE_BOARD_HEIGHT)


inline gs_tictactoe_space_state gs_tictactoe_getSpaceState(gs_tictactoe const game, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos]);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_space_state gs_tictactoe_setSpaceState(gs_tictactoe game, gs_tictactoe_space_state const state, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos] = state);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_index gs_tictactoe_reset(gs_tictactoe game)
{
	gs_tictactoe_index xpos, ypos, total;
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
			game[xpos][ypos] = gs_tictactoe_space_open;
	total = (xpos * ypos);
	return total;
}

inline gs_tictactoe_index gs_tictactoe_print(gs_tictactoe game)
{
	cout << "Printing Board..." << endl;
	gs_tictactoe_index xpos, ypos, total;
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
	{
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
		{
			gs_tictactoe_space_state currentSpace =  gs_tictactoe_getSpaceState(game, xpos, ypos);
			char outputVal = ' ';
			switch (currentSpace)
			{
			case gs_tictactoe_space_o:
				outputVal = 'O';
				break;
			case gs_tictactoe_space_x:
				outputVal = 'X';
				break;
			default:
				break;
			}
			cout << outputVal << " ";
		}
		cout << endl;
	}
	total = (xpos * ypos);
	return total;
}

inline gs_tictactoe_space_state gs_tictactoe_checkWin(gs_tictactoe game)
{
	/*
	Check row for win
	*/
	for (int ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
	{
		gs_tictactoe_space_state columnOne = gs_tictactoe_getSpaceState(game, ypos, 0);
		gs_tictactoe_space_state columnTwo = gs_tictactoe_getSpaceState(game, ypos, 1);
		gs_tictactoe_space_state columnThree = gs_tictactoe_getSpaceState(game, ypos, 2);
		bool areAllColumnsTheSame = (columnOne == columnTwo) && (columnOne == columnThree);
		if (columnOne != gs_tictactoe_space_state::gs_tictactoe_space_open)
		{
			if (areAllColumnsTheSame)
				return columnOne;
		}

	}
	for (int xpos = 0; xpos < GS_TICTACTOE_BOARD_HEIGHT; ++xpos)
	{
		gs_tictactoe_space_state columnOne = gs_tictactoe_getSpaceState(game, 0, xpos);
		gs_tictactoe_space_state columnTwo = gs_tictactoe_getSpaceState(game, 1, xpos);
		gs_tictactoe_space_state columnThree = gs_tictactoe_getSpaceState(game, 2, xpos);
		bool areAllColumnsTheSame = (columnOne == columnTwo) && (columnOne == columnThree);
		if (columnOne != gs_tictactoe_space_state::gs_tictactoe_space_open)
		{
			if (areAllColumnsTheSame)
				return columnOne;
		}
	}
	gs_tictactoe_space_state diagonalOne = gs_tictactoe_getSpaceState(game, 0, 0);
	gs_tictactoe_space_state diagonalTwo= gs_tictactoe_getSpaceState(game, 1, 1);
	gs_tictactoe_space_state diagonalThree= gs_tictactoe_getSpaceState(game, 2, 2);
	bool areDiagonalsTheSame = (diagonalOne == diagonalTwo) && (diagonalOne == diagonalThree);
	if (diagonalOne != gs_tictactoe_space_state::gs_tictactoe_space_open)
	{
		if (areDiagonalsTheSame)
			return diagonalOne;
	}
	diagonalOne = gs_tictactoe_getSpaceState(game, 2, 0);
	diagonalTwo = gs_tictactoe_getSpaceState(game, 1, 1);
	diagonalThree = gs_tictactoe_getSpaceState(game, 0, 2);
	 areDiagonalsTheSame = (diagonalOne == diagonalTwo) && (diagonalOne == diagonalThree);
	if (diagonalOne != gs_tictactoe_space_state::gs_tictactoe_space_open)
	{
		if (areDiagonalsTheSame)
			return diagonalOne;
	}
	unsigned char openSpaces = 0;
	for (unsigned char xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
	{
		for (unsigned char ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
		{
			gs_tictactoe_space_state currentSpace = gs_tictactoe_getSpaceState(game, xpos, ypos);
			if (currentSpace == gs_tictactoe_space_state::gs_tictactoe_space_open)
				++openSpaces;
		}
	}
		if(openSpaces > 0)
			return gs_tictactoe_space_state::gs_tictactoe_space_open;
		return gs_tictactoe_space_state::gs_tictactoe_space_invalid;
}

//-----------------------------------------------------------------------------
// DEFINITIONS

int launchTicTacToe()
{
	gs_tictactoe game;
	gs_tictactoe_reset(game);
	gs_tictactoe_space_state currentPlayerState = gs_tictactoe_space_state::gs_tictactoe_space_invalid;
	gs_tictactoe_space_state gameWinner = gs_tictactoe_space_state::gs_tictactoe_space_open;
	char currentPlayer = 'X';

	while (gameWinner == gs_tictactoe_space_state::gs_tictactoe_space_open)
	{
		switch (currentPlayerState)
		{
		case gs_tictactoe_space_o:
		{
			currentPlayerState = gs_tictactoe_space_x;
			currentPlayer = 'X';
		}
		break;
		case gs_tictactoe_space_x:
		{
			currentPlayerState = gs_tictactoe_space_o;
			currentPlayer = '0';
			break;
		}
		default:
		{
			currentPlayerState = gs_tictactoe_space_x;
			currentPlayer = 'X';
			break;
		}
		}
		gs_tictactoe_space_state spaceState = gs_tictactoe_space_state::gs_tictactoe_space_invalid;
		int x, y;
		while (spaceState != gs_tictactoe_space_state::gs_tictactoe_space_open) // Update to be if it's not the piece we are either
		{
			cout << "Player: " << currentPlayer << " enter your input. "<< endl;
			cout << "Enter the X pos [1-3]." << endl;
			cin >> y;
			cout << "Enter the Y pos [1-3]." << endl;
			cin >> x;
			x -= 1;
			y -= 1;
			spaceState = gs_tictactoe_getSpaceState(game, x, y);
			if (spaceState != gs_tictactoe_space_state::gs_tictactoe_space_open)
			{
				cout << "Invalid placement" << endl;
			}
		}
		gs_tictactoe_setSpaceState(game, currentPlayerState, x, y);
		gs_tictactoe_print(game);
		gameWinner = gs_tictactoe_checkWin(game);
	}
	if(gameWinner != gs_tictactoe_space_state::gs_tictactoe_space_invalid)
	cout << "Winner for: " << currentPlayer << endl;
	else
		cout << "Tie Game." << endl;

	return 0;
}


//-----------------------------------------------------------------------------
