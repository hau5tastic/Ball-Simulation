#pragma once
#include "Ball.h"
#include <SDL.h>

class cannonBall : public GameObj
{
public:
	cannonBall(Vec2<float> position, Vec2<float> velocity);
	~cannonBall();
	void render(SDL_Surface* surface);
};

