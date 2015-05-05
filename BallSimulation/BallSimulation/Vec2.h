#pragma once
#include <math.h>

template <class t> struct Vec2
{
	float x, y;

	inline void init(float _x, float _y)
	{
		x = _x; y = _y;
	}

	inline Vec2(float _x, float _y)
	{
		init(_x, _y);
	}

	inline Vec2(float _s = float(0.0))
	{
		init(_s, _s);
	}

	inline const Vec2 operator + (const Vec2& v) const
	{
		return Vec2(x + v.x, y + v.y);
	}

	inline const Vec2 operator - (const Vec2& v) const
	{
		return Vec2(x - v.x, y - v.y);
	}

	inline const Vec2 operator * (const float s) const
	{
		return Vec2(x * s, y * s);
	}

	inline friend const Vec2 operator * (const float s, const Vec2& v)
	{
		return v * s;
	}
	
	inline const Vec2 operator / (const float s) const
	{
		return Vec2(x / s, y / s);
	}

	inline Vec2& operator += (const Vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	inline Vec2& operator -= (const Vec2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	inline Vec2& operator *= (const float s)
	{
		x *= s;
		y *= s;
		return *this;
	}
};