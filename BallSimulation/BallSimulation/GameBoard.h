#pragma once
#include <SDL.h>
#include "Vec2.h"

class GameBoard
{
private:
	/// Create the standard 4:3 game window dimensions
	/// "const" is considered better than define statements,
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	float gridWidth, gridHeight, gridX, gridY;
	float x, y;
	SDL_Window* window;   ///(NULL is defined in stdio.h as a zero) 
	SDL_Surface* surface;

public:
	GameBoard(int width, int height, int gridX, int gridY);
	~GameBoard();
	SDL_Surface* getSurface();
	SDL_Rect getSurfaceRect();
	SDL_Window* getWindow();
	void render();
	int getHeight();
	Vec2<float> GameBoard::convertToScreenCoordinates(int x, int y);
	Vec2<float> getScreenCoordinates(float x, float y);
};

