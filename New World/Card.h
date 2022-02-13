#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
/*
	Stores the information about the playing card
*/
class Card
{
public:
	Card(); //contructor for an empty card
	Card(uint8_t, SDL_Renderer*); //negative numbers for land cards and positive numbers for action cards
	~Card();
	SDL_Texture* getTexture();
private:
	SDL_Texture* tex = nullptr;
	uint8_t id;
};

