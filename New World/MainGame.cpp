#include "MainGame.h"

//shows the error and waits for the user to enter a key
void MainGame::fatalError(std::string errorString) {
	std::cerr << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	clean();
	exit(-1);
}

//Contructor
MainGame::MainGame(int _windowWidth, int _windowHeight) {
	window = nullptr;
	renderer = nullptr;
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

//Destructor
MainGame::~MainGame() {
	delete(board);
	clean();
}


//Initialize Systems
void MainGame::initSystems(const char* title, bool fullscreen) {
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL Initialised" << std::endl;
		if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))//initialize SDL2_images
			std::cout << "SDL Image Initialised" << std::endl;
		else fatalError("SDL_Image could not be initialised");

		//open window
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags);
		if (window) //check if created
			std::cout << "SDL Window Created" << std::endl;
		else
			fatalError("SDL Window could not be created");

		//create the renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) //check if created
			std::cout << "SDL Renderer created" << std::endl;
		else
			fatalError("SDL Renderer could not be created");

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //set background to white

		isRunning = true;
	}
	else {
		fatalError("SDL could not be initialised");
	}
	initTextures();
	//init board
	board = new Board(renderer,boardTex);
}

void MainGame::initTextures() {
	//create a texture where the fractal can be drawn on
	boardTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, windowWidth, windowHeight);
	if (!boardTex)
		fatalError("Board texture could not be created\n");
	//init textures here using createTexture(filePath,tex);
	createTexture("assets/TestBackground.png", backgroundTex);
}

void MainGame::createTexture(const char* filePath, SDL_Texture* &tex) {
	SDL_Surface* tmpSurface = IMG_Load(filePath); //create temporary surface
	tex = SDL_CreateTextureFromSurface(renderer, tmpSurface); //turn surface into texture
	if (!tex) fatalError("Texture could not be loaded!"); //check if succesfull
	SDL_FreeSurface(tmpSurface); //free up the surface
}

//proccesses user input
void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) { //while there is an event, (somethings happens)
		//see what event it is
		switch (event.type) {
		case SDL_QUIT: //when the red cross is pressed
			isRunning = false;
			break;
		case SDL_KEYDOWN: //when a key is pressed
			break;
		case SDL_MOUSEBUTTONDOWN: //when mouse is presed 
			if (event.button.button == SDL_BUTTON_LEFT) {
				//testing if clicked inside the hexagon (cirle)
				if ((event.button.x - 610) * (event.button.x - 610) + (event.button.y - 195) * (event.button.y - 195) < 111 * 111) {
					std::cout << "Clicked on Hexagon\n";
					board->startPlacingTile();
					board->getTexture(boardTex);
				}
			}
			break;
		}
	}
}

//update
void MainGame::update() {
	
}

//render to screen
void MainGame::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1); //set background to white
	SDL_RenderClear(renderer);
	//things to render
	SDL_RenderCopy(renderer,backgroundTex,NULL,NULL);
	SDL_RenderCopy(renderer, boardTex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

//clean the game
void MainGame::clean() {
	//SDL_DestroyTexture(TextureName); //destroy texture
	SDL_DestroyWindow(window); //destroy the window
	SDL_DestroyRenderer(renderer); //destroy the renderer
	SDL_DestroyTexture(backgroundTex); //destroy background texture
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}