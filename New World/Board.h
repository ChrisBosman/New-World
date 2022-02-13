#pragma once
#include "SDL.h"
#include "Deck.h"
#include "Card.h"

class Board
{
public:
	//functions
	Board(SDL_Renderer*);
	~Board();
	void startPlacingTile(); //start the placement of the tile
private:
	//-------------functions---------------\\

	void proccesUserInput(Card*); //procces the user input
	void render(SDL_Texture*,Card*); //render the placement of the tile
	bool tryPlacingTile(__int16, __int16); //try to place the tile
	

	//-------------variables---------------\\

	SDL_Renderer* renderer;
	bool isPlacingTile = false; //if the user is placing a tile right now.
	__int16 mousePosX=0, mousePosY=0; //the mouse positions
	Deck* landDeck = nullptr;

};

