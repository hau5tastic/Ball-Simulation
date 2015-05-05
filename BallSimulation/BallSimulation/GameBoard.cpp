#include "GameBoard.h"
#include <stdio.h>

// constructor
GameBoard::GameBoard(int width, int height, int GridX, int GridY)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	gridX = GridX;
	gridY = GridY;
	gridWidth = SCREEN_WIDTH / gridX;
	gridHeight = SCREEN_HEIGHT / gridY;

	window = NULL;   ///(NULL is defined in stdio.h as a zero) 
	surface = NULL;

	/// Create the window
	window = SDL_CreateWindow("My First Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("SDL_Error: %s\n", SDL_GetError());
	}
	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
}


GameBoard::~GameBoard()
{
	/// Kill the window
	SDL_DestroyWindow(window);
}

SDL_Surface* GameBoard::getSurface()
{
	return surface;
}

SDL_Rect GameBoard::getSurfaceRect()
{
	SDL_Rect surfaceRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	return surfaceRect;
}

SDL_Window* GameBoard::getWindow()
{
	return window;
}

void GameBoard::render()
{
	SDL_UpdateWindowSurface(window);
}

Vec2<float> GameBoard::convertToScreenCoordinates(int x, int y)
{
	return Vec2<float>(x * gridWidth, SCREEN_HEIGHT -  (y * gridHeight));
}

Vec2<float> GameBoard::getScreenCoordinates(float X, float Y)
{
	return Vec2<float>((X / SCREEN_WIDTH), (SCREEN_HEIGHT - (Y / SCREEN_HEIGHT)));
}