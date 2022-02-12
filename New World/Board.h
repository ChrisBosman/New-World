#pragma once
#include "SDL.h"

class Board
{
public:
	//functions
	Board();
	~Board();
	void startPlacingTile(); //start the placement of the tile
private:
	//functions
	void proccesUserInput(); //procces the user input
	void render(); //render the placement of the tile
	bool tryPlacingTile(__int16, __int16); //try to place the tile
	//variables
	bool isPlacingTile = false; //if the user is placing a tile right now.
	__int16 mousePosX, mousePosY; //the mouse positions
};

