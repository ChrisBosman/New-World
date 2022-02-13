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
	Card(int8_t, SDL_Renderer*); //negative numbers for land cards and positive numbers for action cards
	~Card();
	SDL_Texture* getTexture();
	int16_t getRotation() { return rotation; };
	void rotateLeft();
	void rotateRight();
private:
	SDL_Texture* tex = nullptr;
	int8_t id;
	int16_t rotation = 0; //in degrees
};

