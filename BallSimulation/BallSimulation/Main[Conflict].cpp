#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL.h>
#include "gameBoard.h"
#include "Ball.h"
#include "Vec2.h"

/// Prototyping
Uint32  handleTimer(Uint32 interval, void *param);  
Vec2 getRandomVector(int rangeX, int rangeY);

GameBoard *win; /// Make this global 
Ball *balls[8];	  /// Make this global 
int numberOfBalls = sizeof(balls) / sizeof(balls[0]);

int main(int argc, char* args[]) { /// Standard C-style entry point

	SDL_Event event;	/// An SDL Event object
	SDL_TimerID timer;
	
	srand((unsigned)time(NULL));

	win = new GameBoard(800, 480);

	for (int i = 0; i < numberOfBalls; i++)
	{
		balls[i] = new Ball(getRandomVector(700, 200), getRandomVector(200, 200));
	}

	//balls[5] = new Ball(getRandomVector(100), getRandomVector(1000));

	timer = SDL_AddTimer(33, handleTimer, NULL);

	/// Check for an input event
	while (SDL_WaitEvent(&event)) {
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_SPACE)){
			exit(0);
		}
	}

	/// Kill the window
	SDL_DestroyWindow(win->getWindow());

	//delete ball;
	delete win;

	///Exit the SDL subsystems
	SDL_Quit();
	exit(0);
}

Uint32  handleTimer(Uint32 interval, void *param){
	//SDL_UpdateWindowSurface(win->getWindow());
	win->render();
	for (int i = 0; i < numberOfBalls; i++)
	{	
		balls[i]->update(win->getSurfaceRect(), (float)interval);
		balls[i]->render(win->getSurface());
	}
	
	//printf("timer %d\n", interval);
	return interval;
}

Vec2 getRandomVector(int rangeX, int rangeY)
{
	int randX = rand() % rangeX + 1;
	int randY = rand() % rangeY + 1;
	printf("[%d, %d]\n", randX, randY); 
	return Vec2((float)randX, (float)(randY));
}