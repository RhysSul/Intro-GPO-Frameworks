
#include <stdio.h>
#include <iostream>
#include "GPRO-FW-3000/display.h"
using namespace std;

//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_BATTLESHIP_PLAYERS				2
#define GS_BATTLESHIP_BOARD_WIDTH			10
#define GS_BATTLESHIP_BOARD_HEIGHT			10

enum gs_battleship_space_state
{
	// invalid space state
	gs_battleship_space_invalid = -1,

	// states visible to both players
	gs_battleship_space_open,			// space is open and unguessed
	gs_battleship_space_miss,			// space was guessed and missed
	gs_battleship_space_hit,			// space was guessed and hit

	// states hidden from opponent player
	gs_battleship_space_patrol2,		// 2-unit patrol boat
	gs_battleship_space_submarine3,		// 3-unit submarine
	gs_battleship_space_destroyer3,		// 3-unit destroyer
	gs_battleship_space_battleship4,	// 4-unit battleship
	gs_battleship_space_carrier5,		// 5-unit carrier
};
#ifndef __cplusplus
typedef		enum gs_battleship_space_state	gs_battleship_space_state;
#endif	// !__cplusplus

// battleship game state
typedef		unsigned char					gs_battleship_index;
typedef		gs_battleship_space_state		gs_battleship[GS_BATTLESHIP_PLAYERS][GS_BATTLESHIP_BOARD_WIDTH][GS_BATTLESHIP_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,z,w,h,d)		(x < w && y < h && z < d)
#define GS_BATTLESHIP_VALID(p,x,y)				GS_VALIDATE_COORDINATE(x,y,p,GS_BATTLESHIP_BOARD_WIDTH,GS_BATTLESHIP_BOARD_HEIGHT,GS_BATTLESHIP_PLAYERS)


inline gs_battleship_space_state gs_battleship_getSpaceState(gs_battleship const game, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos]);
	return gs_battleship_space_invalid;
}

inline gs_battleship_space_state gs_battleship_setSpaceState(gs_battleship game, gs_battleship_space_state const state, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos] = state);
	return gs_battleship_space_invalid;
}

inline gs_battleship_index gs_battleship_reset(gs_battleship game)
{
	gs_battleship_index player, xpos, ypos, total;
	for (player = 0; player < GS_BATTLESHIP_PLAYERS; ++player)
		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
			for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
				game[player][xpos][ypos] = gs_battleship_space_open;
	total = (player * xpos * ypos);
	return total;
}

inline void gs_battleship_print(gs_battleship game, gs_battleship_index player)
{
	gs_battleship_index xpos, ypos;
	for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
	{
		for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
		{
			char outputSpace = 'N';
			switch (gs_battleship_getSpaceState(game, player, xpos, ypos))
			{
			case gs_battleship_space_open:
				outputSpace = '#';
				break;
			case gs_battleship_space_miss:
				outputSpace = 'O';
				break;
			case gs_battleship_space_hit:
				outputSpace = 'X';
				break;
			case gs_battleship_space_patrol2:
				 outputSpace = 'P';
				break;
			case gs_battleship_space_submarine3:
				 outputSpace = 'S';
				break;
			case gs_battleship_space_destroyer3:
				 outputSpace = 'D';
				break;
			case gs_battleship_space_battleship4:
				 outputSpace = 'B';
				break;
			case gs_battleship_space_carrier5:
				 outputSpace = 'C';
				break;
			default:
				break;
			}
		}
	}
}

inline void gs_battleship_printOpponentsBoard(gs_battleship game, gs_battleship_index player)
{
	gs_battleship_index xpos, ypos;
	int otherPlayer = 0;
	if (player == otherPlayer)
		otherPlayer = 1;
	for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
	{
		for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
		{
			char outputSpace = 'N';
			switch (gs_battleship_getSpaceState(game, otherPlayer, xpos, ypos))
			{
			case gs_battleship_space_open:
				outputSpace = '#';
				break;
			case gs_battleship_space_miss:
				outputSpace = 'O';
				break;
			case gs_battleship_space_hit:
				outputSpace = 'X';
				break;
			default:
				outputSpace = '#';
				break;
			}
			cout << outputSpace << " ";
		}
		cout << endl;
	}
}
inline gs_battleship_space_state gs_battleship_testSpace(gs_battleship  game, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	gs_battleship_index otherPlayer = 0;
	if (otherPlayer == player)
		otherPlayer = 1;

	switch (gs_battleship_getSpaceState(game, otherPlayer, xpos, ypos))
	{
	case gs_battleship_space_open:
	{
		gs_battleship_setSpaceState(game, gs_battleship_space_miss, otherPlayer, xpos, ypos);
		return gs_battleship_space_miss;
	}
	default:
	{
		gs_battleship_setSpaceState(game, gs_battleship_space_hit, otherPlayer, xpos, ypos);
		return gs_battleship_space_hit;
	}
	return gs_battleship_space_invalid;
	}
}

//-----------------------------------------------------------------------------
// DEFINITIONS

void gs_battleship_inGameLoop(gs_battleship& game, gs_battleship_index& currentPlayer);

inline void gs_battleship_placeShip(gs_battleship& game, const gs_battleship_index& currentPlayer, const int& shipLength, const gs_battleship_space_state& shipToPlace);

inline void gs_battleship_setupLoop(gs_battleship& game)
{
	// 5 piece
	// 4 piece
	// 2 3s
	// 2
	// total of 17
	gs_battleship_index currentPlayer = 0;
	while(currentPlayer != 2)
	{
	clearScreen();
	cout << "Currently playing the carrier (5 spaces): CCCCC" << endl;
	gs_battleship_print(game, currentPlayer);
	gs_battleship_placeShip(game, currentPlayer, 5, gs_battleship_space_carrier5);
	gs_battleship_print(game, currentPlayer);
	clearScreen();

	cout << "Currently placing the battleship (4 spaces): BBBB " << endl;
	gs_battleship_print(game, currentPlayer);
	gs_battleship_placeShip(game, currentPlayer, 4, gs_battleship_space_battleship4);
	gs_battleship_print(game, currentPlayer);
	clearScreen();

	cout << "Currently placing the destroyer (3 spaces): DDD " << endl;
	gs_battleship_print(game, currentPlayer);
	gs_battleship_placeShip(game, currentPlayer, 3, gs_battleship_space_destroyer3);
	gs_battleship_print(game, currentPlayer);
	clearScreen();

	cout << "Currently placing the submarine (3 spaces): SSS " << endl;
	gs_battleship_print(game, currentPlayer);
	gs_battleship_placeShip(game, currentPlayer, 3, gs_battleship_space_submarine3);
	gs_battleship_print(game, currentPlayer);
	clearScreen();

	cout << "Currently placing the destroyer (2 spaces): PP" << endl;
	gs_battleship_print(game, currentPlayer);
	gs_battleship_placeShip(game, currentPlayer, 2, gs_battleship_space_patrol2);
	gs_battleship_print(game, currentPlayer);
	++currentPlayer;
	}
	clearScreen();
	cout << "Setup Finished." << endl;
}

inline void gs_battleship_placeShip(gs_battleship& game, const gs_battleship_index& currentPlayer, const int &shipLength, const gs_battleship_space_state &shipToPlace)
{

	gs_battleship_space_state spaceState = gs_battleship_space_state::gs_battleship_space_invalid;

	int x, y, rotation;
	while (spaceState != gs_battleship_space_state::gs_battleship_space_open) // Update to be if it's not the piece we are either
	{
		cout << "Enter 0 to place the battleship horizontally, 1 to place it vertically." << endl;
		cin >> rotation;
		cout << "Enter the X pos of where to start the placement[1-10]." << endl;
		cin >> y;
		cout << "Enter the Y pos of where start the placement[1-10]." << endl;
		cin >> x;
		x -= 1;
		y -= 1;

		spaceState = gs_battleship_space_open;

		if (rotation == 1)
		{
			for (int i = x; i < x + shipLength; ++i)
			{
				if (gs_battleship_getSpaceState(game, currentPlayer, i, y) != gs_battleship_space_open)
					spaceState = gs_battleship_space_invalid;
			}
		}
		else
		{
			for (int i = y; i < y + shipLength; ++i)
			{
				if (gs_battleship_getSpaceState(game, currentPlayer, x, i) != gs_battleship_space_open)
				{
					spaceState = gs_battleship_space_invalid;
				}
			}
		}

		if (spaceState == gs_battleship_space_invalid)
			cout << "Invalid placement." << endl;
	}

	if (rotation == 1)
	{
		for (int i = x; i < x + shipLength; ++i)
		{
			gs_battleship_setSpaceState(game, shipToPlace, currentPlayer, i, y);
		}
	}
	else
	{
		for (int i = y; i < y + shipLength; ++i)
		{
			gs_battleship_setSpaceState(game, shipToPlace, currentPlayer, x, i);
		}
	}
}

int launchBattleship()
{
	cout << "Welcome to battleship! " << endl;
	gs_battleship game;

	gs_battleship_reset(game);

	gs_battleship_index currentPlayer = 0;

	gs_battleship_setupLoop(game);
	gs_battleship_inGameLoop(game, currentPlayer);

	return 0;
}

inline gs_battleship_index gs_battleship_detectWin(gs_battleship& game)
{
	gs_battleship_index xpos, ypos;
	for (gs_battleship_index player = 0; player < GS_BATTLESHIP_PLAYERS; ++player)
	{
		int numHits = 0;
		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
		{
			for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
			{
				if (gs_battleship_getSpaceState(game, player, xpos, ypos) == gs_battleship_space_hit)
				{
					++numHits;
				}
			}
		}
		if (numHits >= 17)
		{
			return player;
		}
	}
	return -1;
}

void gs_battleship_inGameLoop(gs_battleship& game, gs_battleship_index& currentPlayer)
{
	gs_battleship_index loser = -1;
	while (loser != -1)
	{
		int b = 0;
		while (b == 0)
		{
			cout << "Enter 1 when ready to start your turn player: " << "X" << "." << endl;
			cin >> b;
		}

		cout << "Your board is: " << endl;
		gs_battleship_print(game, currentPlayer);

		cout << "Opponents Board:" << endl;
		gs_battleship_printOpponentsBoard(game, currentPlayer);

		bool hasFoundValidSpace = false;
		int x, y;
		while (!hasFoundValidSpace) // Update to be if it's not the piece we are either
		{
			cout << "Enter the X pos [1-10]." << endl;
			cin >> y;
			cout << "Enter the Y pos [1-10]." << endl;
			cin >> x;
			x -= 1;
			y -= 1;
			int otherPlayer = 0;
			if (otherPlayer == currentPlayer)
				otherPlayer = 1;

			auto spaceState = gs_battleship_getSpaceState(game, otherPlayer, x, y);
			switch (spaceState)
			{
			case gs_battleship_space_patrol2:
				hasFoundValidSpace = true;
				break;
			case gs_battleship_space_submarine3:
				hasFoundValidSpace = true;
				break;
			case gs_battleship_space_destroyer3:
				hasFoundValidSpace = true;
				break;
			case gs_battleship_space_battleship4:
				hasFoundValidSpace = true;
				break;
			case gs_battleship_space_carrier5:
				hasFoundValidSpace = true;
				break;
			case gs_battleship_space_open:
				hasFoundValidSpace = true;
				break;
			default:
				hasFoundValidSpace = false;
				break;
			}
		}

		switch (gs_battleship_testSpace(game, currentPlayer, x, y) )
		{
		case gs_battleship_space_hit:
			cout << "Hit!" << endl;
			break;
		case gs_battleship_space_miss:
			cout << "Miss!" << endl;
			break;
		default:
			break;
		}
		cout << "Opponents Board:" << endl;
		gs_battleship_printOpponentsBoard(game, currentPlayer);

		int i = 0;
		while (i == 0)
		{
			cout << "Enter 1 when ready to end your turn." << endl;
			cin >> i;
		}

		if (currentPlayer == 0)
			currentPlayer = 1;
		else
			currentPlayer = 0;
		clearScreen();
		loser = gs_battleship_detectWin(game);
	}
	char winnerName = '1';
	if (loser == 1)
		winnerName = '2';
	cout << "Congratulations Player: " << winnerName << " you win!" << endl;
}


//-----------------------------------------------------------------------------
