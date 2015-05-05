#pragma once
#include <SDL.h>
#include "GameObj.h"
#include "Vec2.h"

class Ball : public GameObj
{
protected:

public:
	Ball(Vec2<float> position, Vec2<float> velocity);
	~Ball();
	void render(SDL_Surface* surface);
};

