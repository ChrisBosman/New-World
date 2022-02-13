#include "Board.h"
//constructor
Board::Board(SDL_Renderer* _renderer)
:renderer(_renderer)
{
	//create a deck for the landCards
	std::vector<Card*> landCards;
	for(uint8_t i = 0; i<10; i++)
		landCards.push_back(new Card((rand()%3+1)*-1,renderer));
	landDeck = new Deck(landCards);
}

//destructor
Board::~Board() {
	delete(landDeck);
}

/*
What happens when you start placing a tile, so display the tile at
the posistion of the mouse, rotate it with q and e. And place it by
left clicking
*/
void Board::startPlacingTile() {
	//peek at a card from the pile of land cards (landDeck)
	SDL_Texture* cardTex;
	Card* card = landDeck->peekCard();
	cardTex = card->getTexture();
	isPlacingTile = true; //the user is now placing a tile
	while (isPlacingTile)
	{
		proccesUserInput(card);
		render(cardTex,card);
	}
}

void Board::proccesUserInput(Card* card) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) { //while there is an event, (somethings happens)
		//see what event it is
		switch (event.type) {
		case SDL_QUIT: //when the red cross is pressed
			isPlacingTile = false;
			break;
		case SDL_KEYDOWN: //when a key is pressed
			switch (event.key.keysym.sym)
			{
			case 'q': //rotate left
				card->rotateLeft();
				break;
			case 'e': //rotate right
				card->rotateRight();
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN: //when mouse is presed
			if (event.button.button == SDL_BUTTON_LEFT)
				tryPlacingTile(event.button.x, event.button.y); //try to place a tile
				break;
		case SDL_MOUSEMOTION: //when the mouse moves
			mousePosX = event.motion.x;
			mousePosY = event.motion.y;
		}
	}
}

void Board::render(SDL_Texture* tex, Card* card)
{
	SDL_Rect destRect;
	destRect.h = 64; destRect.w = 64;
	destRect.x = mousePosX - 32; destRect.y = mousePosY - 32;
	SDL_RenderClear(renderer);
	SDL_RenderCopyEx(renderer, tex, NULL, &destRect,card->getRotation(),NULL,SDL_FLIP_NONE); //rotate and plot
	SDL_RenderPresent(renderer);
}

bool Board::tryPlacingTile(__int16, __int16)
{
	return false;
}