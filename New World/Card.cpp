#include "Card.h"
//empty constructor
Card::Card() {
	id = 0;
}

//constructor for predefined cards
Card::Card(int8_t _id, SDL_Renderer* renderer) {
	id = _id;
	if (id == 0) { //check if the cards has an id
		std::cout << "Error: Id if card is 0\n";
		return;
	}
	//create texture
	char filePath[31];
	if (id < 0) //land card
		sprintf_s(filePath, "assets/LandCards/Card%i_%i.png", abs(id), rand() % 2 + 1);
	else // action card
		sprintf_s(filePath, "assets/ActionCards/Card%i_%i.png", abs(id), rand() % 2 + 1);
	//create temporary surface
	SDL_Surface* tmpSurface = IMG_Load(filePath); 
	//turn surface into texture
	tex = SDL_CreateTextureFromSurface(renderer, tmpSurface); 
	//check if succesfull
	if (!tex) std::cout << "Texture could not be loaded!\n";
	SDL_FreeSurface(tmpSurface); //free up the surface

}

//deconstructor
Card::~Card() {
	std::cout << "Destroyed card\n";
	SDL_DestroyTexture(tex); //destroy texture
}

SDL_Texture* Card::getTexture(){
	return tex;
}

void Card::rotateLeft(){
	rotation -= 60;
	while (rotation < -360)
		rotation += 360;
}

void Card::rotateRight() {
	rotation += 60;
	while (rotation > 360)
		rotation -= 360;
}