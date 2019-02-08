#include<SDL.h>
#include<stdio.h>
#include<string>

int x = 381;
int y = 290;

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

enum Keys {
	KEYS_UP,
	KEYS_DOWN,
	KEYS_LEFT,
	KEYS_TOTAL,
	Keys_Total
};


bool init();
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Renderer for sprites and geometric shape
SDL_Renderer* gRenderer;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gGameSurface = NULL;
SDL_Surface* gSprite1 = NULL;

//Key Press Commands
SDL_Surface* gKeyPress[KEYS_TOTAL];

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError()); success = false;
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("Pac Man", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
			}
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true;
	gGameSurface = SDL_LoadBMP("Background.bmp");
	if (gGameSurface == NULL) {
		printf("SDL could not load Background! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}

void KeyMovement() {

}

void LoadSprites() {
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);

	SDL_Rect fillRect = { x , y, 37, 37 };
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &fillRect);
	SDL_RenderPresent(gRenderer);
}

void close() {
	for (int i = 0; i < KEYS_TOTAL; i++) {
		SDL_FreeSurface(gKeyPress[i]);
		gKeyPress[i] = NULL;
	}
	SDL_FreeSurface(gScreenSurface);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = true;
						case SDLK_UP:
							y+=-20;
						case SDLK_DOWN:
							y+=20;
						case SDLK_LEFT:
							x+=-20;
						case SDLK_RIGHT:
							x+=20;
						}
					}
				}
//				SDL_BlitSurface(gGameSurface, NULL, gScreenSurface, NULL);
				LoadSprites();
//				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();
	return 0;
}