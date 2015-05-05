#include "GameObj.h"
#include <string>
#include <SDL_video.h>
#include <stdio.h>
#include "VecMath.h"

GameObj::GameObj(Vec2<float> pos, Vec2<float> velo)
{
	time = 0.0f;

	CoefficientOfRestitution = 0.95f;

	position = pos;
	imgRect = { (int)position.x, (int)position.y, 93, 92 };
	origin = Vec2<float>((float)imgRect.w / 2, (float)imgRect.h / 2);
	radius = origin.x;
	center = position + origin;

	initialVelocity = velo;
	velocity = acceleration = force = Vec2<float>();
	//gravityForce = Vec2<float>(0.0f, 9.8f);
	gravityForce = Vec2<float>(0.0f, 980.0f);
}


GameObj::~GameObj()
{
	/// Deallocate surface
	SDL_FreeSurface(Image);
	Image = NULL;
}

// physics
void GameObj::update(SDL_Rect surfaceRect, float elapsedTime)
{
	time = elapsedTime / 1000.0f; // seconds

	center = position + origin;

	// derive position from force using newtonian equations of motion
	force = gravityForce;
	acceleration = force / mass;
	position += (initialVelocity * time) + (0.5 * acceleration * time * time);
	velocity = initialVelocity + (acceleration * time);
	initialVelocity = velocity;

	boundaryCheck(surfaceRect);

	updateRect(position);
}

void GameObj::updateRect(Vec2<float> position)
{
	imgRect.x = (int)position.x;
	imgRect.y = (int)position.y;
}

// boundary checks
void GameObj::boundaryCheck(SDL_Rect surfaceRect)
{
	// bottom
	if (position.y + imgRect.h > surfaceRect.h || position.y < 0)
	{
		if (position.y < 0)
		{
			position.y = 0;
		}
		else
		{
			position.y = (float)surfaceRect.h - imgRect.h;
		}
		initialVelocity.y *= -1 * CoefficientOfRestitution;
	}
	// sides
	if (position.x + imgRect.w > surfaceRect.w || position.x < 0)
	{
		if (position.x < 0)
		{
			position.x = 0;
		}
		else
		{
			position.x = (float)surfaceRect.w - imgRect.w;
		}
		initialVelocity.x *= -1 * CoefficientOfRestitution;
	}
}

//collision detection
bool GameObj::collisionDetected(GameObj* oGameObj)
{
	float distanceBetween;
	bool collision = false;
	Vec2<float> distance = oGameObj->center - center;

	try
	{
		distanceBetween = VecMath::mag(distance);
	}
	catch (std::string se)
	{
		std::fstream log;
		log.open("log.txt", std::ios::app);
		log << se << "\n";
		log.close();
	}

	if (distanceBetween < (oGameObj->radius + radius))
	{
		collision = true;

		// prevent orbiting
		Vec2<float> normal = distance;
		Vec2<float> normalizedNormal = VecMath::norm(normal);
		while (VecMath::mag(normal) < (oGameObj->radius + radius) + 2)
		{
			position += normalizedNormal * -1;
			oGameObj->position += normalizedNormal;
			normal = (oGameObj->position + oGameObj->origin) - (position + origin);
		}
		updateRect(position);
		oGameObj->updateRect(oGameObj->position);
	}
	return collision;
}

// dynamic collision response
void GameObj::resolveCollision(GameObj* oGameObj)
{
	Vec2<float> normal = oGameObj->center - center;

	normal = VecMath::norm(normal);

	float vi1norm = VecMath::dot(initialVelocity, normal);
	float vi2norm = VecMath::dot(oGameObj->initialVelocity, normal);

	float vf1norm = (((mass - CoefficientOfRestitution * oGameObj->mass) * vi1norm) + ((1 + CoefficientOfRestitution) * oGameObj->mass * vi2norm)) / (mass + oGameObj->mass);
	float vf2norm = (((oGameObj->mass - CoefficientOfRestitution * mass) * vi2norm) + ((1 + CoefficientOfRestitution) * mass * vi1norm)) / (mass + oGameObj->mass);

	float v1norm = vf1norm - vi1norm;
	float v2norm = vf2norm - vi2norm;

	initialVelocity = initialVelocity + v1norm * normal;
	oGameObj->initialVelocity = oGameObj->initialVelocity + v2norm * normal;
}

