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

	ResourceManager::ResourceManager resourceManager = ResourceManager::ResourceManager(gameRenderer);

	resourceManager.AddConfig("Config", "config.json");
	resourceManager.AddConfigElement("Config", "Game_Name", "GameName");
	resourceManager.AddConfigElement("Config", "Message", "Message");

	resourceManager.AddFont("Font", "ComicSans.ttf", 18);
	resourceManager.AddTexture("Texture", "demon.png");
	resourceManager.AddMusic("GameMusic", "gameMusic.wav");
	resourceManager.AddSound("GameSound", "gameSound.wav");
	resourceManager.AddMap("Map", "map.json");

	SDL_Rect holder = SDL_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	Mix_PlayMusic(resourceManager.GetMusic("GameMusic"), -1);
	int counter = 200;

	while (gameRunning)
	{
		//Update Code
		resourceManager.Update();

		SDL_SetWindowTitle(gameWindow, resourceManager.GetConfigElement("Config", "Game_Name").c_str());
		if (counter > 0)
		{
			counter--;
		}
		else
		{
			Mix_PlayChannel(-1, resourceManager.GetSound("GameSound"), 0);
			counter = 200;
		}
		//end update code

		//draw code
		SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gameRenderer);

		SDL_RenderCopy(gameRenderer, resourceManager.GetTexture("Texture"), &holder, &holder);

		//TextStuff
		SDL_Surface *surfaceMessage = TTF_RenderText_Blended(resourceManager.GetFont("Font"), resourceManager.GetConfigElement("Config", "Message").c_str(), SDL_Color{ 0,0,0,0 });
		SDL_Texture *message = SDL_CreateTextureFromSurface(gameRenderer, surfaceMessage);
		SDL_Rect temp = { 0, 0, surfaceMessage->w, surfaceMessage->h };
		SDL_RenderCopy(gameRenderer, message, NULL, &temp);
		SDL_DestroyTexture(message);
		SDL_FreeSurface(surfaceMessage);
		//

		//end draw code
		SDL_RenderPresent(gameRenderer);
	}
	

	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);

	SDL_Quit();

	return 0;
}
