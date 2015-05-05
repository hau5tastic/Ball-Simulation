#pragma once
#include <SDL.h>
#include "VecMath.h"

class GameObj
{
protected:
	SDL_Surface* Image;
	SDL_Rect imgRect;
	Vec2<float> origin, center;
	Vec2<float> initialVelocity, velocity;
	Vec2<float> force, gravityForce, acceleration;
	float radius, mass, time, CoefficientOfRestitution;

public:
	Vec2<float> position;
	GameObj(Vec2<float> position, Vec2<float> velocity);
	~GameObj();
	virtual void render(SDL_Surface* surface) = 0;
	void update(SDL_Rect surfaceRect, float elapsedTime);
	void updateRect(Vec2<float> position);
	void boundaryCheck(SDL_Rect surfaceRect);
	bool collisionDetected(GameObj* oBall);
	void resolveCollision(GameObj* oBall);
};

