#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include "gameBoard.h"
#include "Ball.h"
#include "cannonBall.h"
#include "Vec2.h"

/// Prototyping
Uint32  handleTimer(Uint32 interval, void *param);  
Vec2<float> getRandomVector(int rangeX, int rangeY);

// Global Variables
GameBoard *win; 
GameObj *balls[8];	 
int numberOfBalls = sizeof(balls) / sizeof(balls[0]);

/// Standard C-style entry point
int main(int argc, char* args[]) { 

	SDL_Event event;	/// An SDL Event object
	SDL_TimerID timer;
	srand((unsigned)time(NULL)); // seed the rand function

	// logging date and time when the application was executed
	time_t rawtime;
	struct tm now;
	time(&rawtime);
	localtime_s(&now, &rawtime);

	std::fstream log;
	log.open("log.txt", std::ios::app);
	log << "Ball Simulation Initialized at: " 
		<< (now.tm_year + 1900) << '-'						   
		<< (now.tm_mon + 1) << '-'
		<< (now.tm_mday) << '@'
		<< (now.tm_hour) << ':'
		<< (now.tm_min) << "\n";
	log.close();

	std::string errors;

	win = new GameBoard(1360, 720, 10, 10);

	int ballType;
	for (int i = 0, x = 1; i < numberOfBalls; i++, x++)
	{	
		ballType = (rand() % 2) + 1;
		try
		{
			if (ballType == 1)
			{
				balls[i] = new Ball((win->convertToScreenCoordinates(x, 9)), getRandomVector(250, 1));
			}
			else if (ballType == 2)
			{
				balls[i] = new cannonBall(win->convertToScreenCoordinates(x, 7), getRandomVector(500, 200));
			}
		}
		
		catch (std::string se)
		{
			errors += "Content Load Exception: " + se + "for ball " + std::to_string(i) + "\n";
		}		
	}

	// append any errors to the file
	log.open("log.txt", std::ios::app);
	log << errors;
	log.close();

	std::cout << errors;

	timer = SDL_AddTimer(16, handleTimer, NULL);

	/// Check for an input event
	while (SDL_WaitEvent(&event)) {
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_SPACE)){
			exit(0);
		}
	}

	/// Kill the window
	SDL_DestroyWindow(win->getWindow());

	for (int i = 0; i < numberOfBalls; i++)
	{
		delete balls[i];
	}
	delete[] balls;
	delete win;

	///Exit the SDL subsystems
	SDL_Quit();
	exit(0);
}

Uint32  handleTimer(Uint32 interval, void *param){
	SDL_FillRect(win->getSurface(), 0, 0);
	
	for (int i = 0; i < numberOfBalls; i++)
	{
		for (int j = i+1; j < numberOfBalls; j++)
		{
			if (balls[j]->collisionDetected(balls[i]))
			{
				balls[j]->resolveCollision(balls[i]);
			}
		}
		balls[i]->update(win->getSurfaceRect(), (float)interval);
		balls[i]->render(win->getSurface());
	}
	win->render();
	//printf("timer %d\n", interval);
	return interval;
}

Vec2<float> getRandomVector(int rangeX, int rangeY)
{
	int directionX = 1;
	if (rand() % 2 + 1 == 2)
	{
		directionX *= -1;
	}
	int x = rand() % rangeX + 1 * directionX;
	int y = rand() % rangeY + 1;
	return Vec2<float>((float)x, float(y));
}