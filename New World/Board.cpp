#include "Board.h"
//constructor
Board::Board(SDL_Renderer* _renderer,SDL_Texture* _tex)
:renderer(_renderer), boardTex(_tex)
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
	if (card == nullptr) //if no card, stop
		return;
	cardTex = card->getTexture();
	isPlacingTile = true; //the user is now placing a tile
	while (isPlacingTile)
	{
		proccesUserInput(card);
		render(cardTex,card);
	}
	landDeck->drawCard(true);
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
				tryPlacingTile(event.button.x, event.button.y,card); //try to place a tile
				break;
		case SDL_MOUSEMOTION: //when the mouse moves
			mousePosX = event.motion.x;
			mousePosY = event.motion.y;

			//testing, get the coords:
			int16_t rTest, qTest,xT,yT;
			pixelToPointyHex(mousePosX, mousePosY, &rTest, &qTest);
			std::cout << "x = " << mousePosX << "\t" << "y = " << mousePosY << "\n";
			std::cout << "r = " << rTest << "\t" << "q = " << qTest << "\n";
			pointyHexToPixel(rTest, qTest, &xT, &yT);
			std::cout << "xT = " << xT << "\t" << "yT = " << yT << "\n";
		}
	}
}

void Board::render(SDL_Texture* tex, Card* card)
{
	SDL_Rect destRect;
	destRect.h = 64; destRect.w = 64;
	destRect.x = mousePosX - 32; destRect.y = mousePosY - 32;
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, boardTex, NULL, NULL);
	SDL_RenderCopyEx(renderer, tex, NULL, &destRect,card->getRotation(),NULL,SDL_FLIP_NONE); //rotate and plot
	SDL_RenderPresent(renderer);
}

void Board::tryPlacingTile(int16_t x, int16_t y,Card* card)
{
	int16_t* r = new int16_t;
	int16_t* q = new int16_t;
	pixelToPointyHex(x, y, r, q);
	if (*r < boardSize && *q < boardSize && *r >= 0 && *q >= 0) {
		if (board[*r][*q + (int16_t)(*r / 2)] == nullptr) {
			board[*r][*q + (int16_t)(*r / 2)] = card;
			isPlacingTile = false;
		}
	}
	//clean up
	delete(r);
	delete(q);
}

//change haxagon (r,q) to pixel (x,y)
void Board::pointyHexToPixel(int16_t r, int16_t q, int16_t* x, int16_t* y){
	*x = hexSize/2 * (sqrt(3) * q + sqrt(3)/2 * r);
	*y = hexSize/2 * (				3.0 / 2 * r);
}

//change pixel (x,y) to hexagon (r,q)
void Board::pixelToPointyHex(int16_t x, int16_t y, int16_t* r, int16_t* q)
{
	//change pixel to hexagonal coordinates (axial)
	
	double q_d = (sqrt(3) / 3 * x - 1. / 3 * y) / (hexSize/2);
	double r_d = (					2. / 3 * y) / (hexSize/2);

	// ---rounding---\\
	//quickly
	double s_d = -q_d - r_d;//since we are using axial we need to calcuate s
	*q = (int16_t)round(q_d);
	*r = (int16_t)round(r_d);
	int16_t s = round(s_d);

	//fix the constraint q+r+s=0
	double q_diff = abs(*q - q_d);
	double r_diff = abs(*r - r_d);
	double s_diff = abs(s - s_d);

	if (q_diff > r_diff && q_diff > s_diff) {
		*q = -*r - s;
	}
	else if(r_diff > s_diff) {
		*r = -*q - s;
	}

}

//render the board to a texture
void Board::getTexture(SDL_Texture* tex){
	//set tex as renderer target
	SDL_SetRenderTarget(renderer, tex); 
	//reset texture
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
	SDL_RenderClear(renderer);
	//draw on the texture
	int16_t* mX = new int16_t;
	int16_t* mY = new int16_t;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] != nullptr) { //if there is a tile
				//het the pixel that is in the center of the hex
				pointyHexToPixel(i, j- (int16_t)(i / 2), mX, mY);
				SDL_Rect destRect;
				destRect.x = *mX - hexSize / 2; destRect.y = *mY - hexSize / 2;
				destRect.h = hexSize; destRect.w = hexSize;
				//draw card
				SDL_RenderCopy(renderer, board[i][j]->getTexture(), NULL, &destRect);
			}
		}
	}
	//delete pointers
	delete(mX);
	delete(mY);
	//reset renderer target
	SDL_SetRenderTarget(renderer, NULL); 
}