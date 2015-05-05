#pragma once
#include "cannonBall.h"
#include <stdio.h>
#include <SDL_video.h>
#include <iostream>
#include <fstream>

cannonBall::cannonBall(Vec2<float> position, Vec2<float> velocity)
	:GameObj(position, velocity)
{
	Image = NULL;

	mass = 10.0f;
	CoefficientOfRestitution = 0.7f;

	Image = SDL_LoadBMP("cannonBall.bmp");
	if (Image == NULL) {
		std::string se = "Error loading cannonBall.bmp";
		throw se;
	}
}


cannonBall::~cannonBall()
{
}

// render function
void cannonBall::render(SDL_Surface* surface)
{
	SDL_SetColorKey(Image, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
	SDL_BlitSurface(Image, NULL, surface, &imgRect);
}