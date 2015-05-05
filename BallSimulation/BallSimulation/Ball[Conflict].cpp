#include "Ball.h"
#include <SDL_video.h>
#include <stdio.h>

Ball::Ball(Vec2 pos, Vec2 velo)
{
	BallImage = NULL;
	time = 0.0f;
	mass = 0.1f;
	CoefficientOfRestitution = 0.9f;

	origin = Vec2((float)ballRect.w / 2, (float)ballRect.h / 2);
	position = pos;
	initialVelocity = velo;
	velocity = acceleration = force = Vec2();
	gravityForce = Vec2(0.0f, 9.8f);

	ballRect = { (int)position.x, (int)position.y, 100, 100 };
	BallImage = SDL_LoadBMP("Ball.bmp");
	//SDL_SetColorKey(BallImage, SDL_SRCCOLORKEY, SDL_MapRGB(BallImage->format, 0, 0, 0));
	if (BallImage == NULL) {
		printf("Error loading bitmap");
	}
}


Ball::~Ball()
{
	/// Deallocate surface
	SDL_FreeSurface(BallImage);
	BallImage = NULL;
}

// render function
void Ball::render(SDL_Surface* surface)
{
	//SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 255, 0, 255));
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
	SDL_FillRect(surface, 0, 0);
	SDL_BlitSurface(BallImage, NULL, surface, &ballRect);
}

// physics
void Ball::update(SDL_Rect surfaceRect, float elapsedTime)
{
	time = elapsedTime / 1000.0f; // seconds



	force = gravityForce;
	acceleration = force / mass;
	position += (initialVelocity * time) + (acceleration * 0.5 * time * time);
	velocity = initialVelocity + (acceleration * time);
	initialVelocity = velocity;

	boundaryCheck(surfaceRect);

	updateRect(position);
}

void Ball::updateRect(Vec2 position)
{
	ballRect.x = (int)position.x;
	ballRect.y = (int)position.y;
}

// boundary checks
void Ball::boundaryCheck(SDL_Rect surfaceRect)
{
	// bottom
	if (position.y + ballRect.h > surfaceRect.h)
	{
		initialVelocity.y *= -1 * CoefficientOfRestitution;
	}
	// sides
	if (position.x + ballRect.w > surfaceRect.w || position.x < 0)
	{
		initialVelocity.x *= -1 * CoefficientOfRestitution;
	}
}
