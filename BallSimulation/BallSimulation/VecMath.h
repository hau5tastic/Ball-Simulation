#pragma once
#include <math.h>
#include "Vec2.h"
#include <iostream>
#include <fstream>

class VecMath
{
public:
	inline static float mag(const Vec2<float>& v)
	{
		float m;

		m = sqrt((v.x * v.x) + (v.y * v.y));
		if (m == 0.0f)
		{
			std::string se = "Divide by Zero Exception";
			throw se;
		}
		else
		{
			return m;
		}
	}

	inline static float dot(const Vec2<float>& v1, const Vec2<float>& v2)
	{
		return ((v1.x * v2.x) + (v1.y * v2.y));
	}

	inline static Vec2<float> norm(const Vec2<float>& v)
	{
		float mag = VecMath::mag(v);
		return Vec2<float>(v.x / mag, v.y / mag);
	}
};