#define SDL_MAIN_HANDLED

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "JSONReader.h"

#include "ResourceManager.h"

using namespace std;
using namespace ResourceManager;

const int SCREEN_WIDTH = 576;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[])
{
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	SDL_Event event;

	bool gameRunning = true;
	bool audio = true;

	gameWindow = SDL_CreateWindow("holder!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	ResourceManager resourceManager = ResourceManager(gameRenderer);

	resourceManager.AddConfig("test", "config.json");
	resourceManager.AddConfigElement("test", "Game_Name", "GameName");

	resourceManager.AddFont("comicsans", "ComicSans.ttf", 18);

	resourceManager.AddTexture("Demon", "demon.png");

	resourceManager.AddMusic("GameMusic", "gameMusic.wav");

	resourceManager.AddSound("GameSound", "gameSound.wav");

	resourceManager.AddMap("mapo", "map.json");

	SDL_SetWindowTitle(gameWindow, resourceManager.GetConfigElement("test", "Game_Name").c_str());

	while (gameRunning)
	{

		resourceManager.Update();

		//end update code
		SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gameRenderer);

		//draw code
		SDL_RendererFlip Flip = SDL_FLIP_NONE;

		//end draw code
		SDL_RenderPresent(gameRenderer);
	}
	

	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);

	SDL_Quit();

	return 0;
}
