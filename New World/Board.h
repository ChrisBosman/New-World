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
	void getTexture(SDL_Texture*); //renders the board on a texture
private:
	//-------------functions---------------\\.
	void proccesUserInput(Card*); //procces the user input
	void render(SDL_Texture*,Card*); //render the placement of the tile
	void tryPlacingTile(int16_t, int16_t,Card*); //try to place the tile
	void pixelToPointyHex(int16_t x, int16_t y, int16_t* r, int16_t* q);
	void pointyHexToPixel(int16_t r, int16_t q, int16_t* x, int16_t* y);

	//-------------variables--------------\\.
	static const int boardSize = 64;
	const uint8_t hexSize = 64;
	SDL_Renderer* renderer;
	bool isPlacingTile = false; //if the user is placing a tile right now.
	int16_t mousePosX=0, mousePosY=0; //the mouse positions
	Deck* landDeck = nullptr;

	Card* board[boardSize][boardSize] = { nullptr }; //Stores all the pointers to the tiles
};

