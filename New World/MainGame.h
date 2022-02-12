/*
	Handels the creation of the game and passes the updata,render and input though
*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

class MainGame
{
public:
	MainGame(int, int);
	~MainGame();

	void initSystems(const char* title, bool fullscreen);

	void processInput();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

private:
	//private functions
	void fatalError(std::string);
	void initTextures();
	void createTexture(const char*,SDL_Texture*&);
	//private variables
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int windowWidth;
	int windowHeight;
	SDL_Texture* backgroundTex = nullptr;
};