#include <iostream>
#include "MainGame.h"
#include <ctime>

int main(int argc, char** argv) {
	srand(time(0)); //made a seed for the rand function
	MainGame* mainGame;
	mainGame = new MainGame(800, 800); //resolution of the screen
	mainGame->initSystems("Game", false);

	while (mainGame->running()) {

		mainGame->processInput();
		mainGame->update();
		mainGame->render();

	}

	delete(mainGame); //clean everything
	return 0;

}