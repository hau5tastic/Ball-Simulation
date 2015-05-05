#pragma once
#include "Ball.h"
#include <stdio.h>
#include <SDL_video.h>
#include <iostream>
#include <fstream>

Ball::Ball(Vec2<float> pos, Vec2<float> velo)
	:GameObj(pos, velo)
{
	Image = NULL;

	mass = 1.0f;

	Image = SDL_LoadBMP("ball.bmp");
	if (Image == NULL) {
		std::string se = "Error loading ball.bmp";
		throw se;
	}
}

Ball::~Ball()
{
	/// Deallocate surface
	SDL_FreeSurface(Image);
	Image = NULL;
}

// render function
void Ball::render(SDL_Surface* surface)
{
	SDL_SetColorKey(Image, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
	SDL_BlitSurface(Image, NULL, surface, &imgRect);
}