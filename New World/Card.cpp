#include "Card.h"
//empty constructor
Card::Card() {
	id = 0;
}

//constructor for predefined cards
Card::Card(uint8_t _id, SDL_Renderer* renderer) {
	id = _id;

	//create texture
	char filePath[10];
	sprintf_s(filePath, "Card%i_%i.png",id,rand()%2+1);
	//create temporary surface
	SDL_Surface* tmpSurface = IMG_Load(filePath); 
	//turn surface into texture
	tex = SDL_CreateTextureFromSurface(renderer, tmpSurface); 
	//check if succesfull
	if (!tex) std::cout << "Texture could not be loaded!";
	SDL_FreeSurface(tmpSurface); //free up the surface
}

//deconstructor
Card::~Card() {
	SDL_DestroyTexture(tex); //destroy texture
}

SDL_Texture* Card::getTexture()
{
	return tex;
}