#include "Board.h"
//constructor
Board::Board() {

}

//destructor
Board::~Board() {

}

/*
What happens when you start placing a tile, so display the tile at
the posistion of the mouse, rotate it with q and e. And place it by
left clicking
*/
void Board::startPlacingTile() {
	isPlacingTile = true; //the user is now placing a tile
	while (isPlacingTile)
	{
		proccesUserInput();
		render();
	}
}

void Board::proccesUserInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) { //while there is an event, (somethings happens)
		//see what event it is
		switch (event.type) {
		case SDL_QUIT: //when the red cross is pressed
			isPlacingTile = false;
			break;
		case SDL_KEYDOWN: //when a key is pressed
			break;
		case SDL_MOUSEBUTTONDOWN: //when mouse is presed
			if (event.button.button == SDL_BUTTON_LEFT)
				tryPlacingTile(event.button.x, event.button.y); //try to place a tile
				break;
		}
	}
}

void Board::render()
{
}

bool Board::tryPlacingTile(__int16, __int16)
{
	return false;
}