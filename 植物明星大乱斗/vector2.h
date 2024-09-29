#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <cmath>

class Vector2
{
public:
	Vector2() = default;
	~Vector2() = default;
	Vector2(float x, float y)
		:x(x), y(y) {}

	float lenth()
	{
		return sqrt(x * x + y * y);
	}
	Vector2 normalize()
	{
		if (x == 0 && y == 0) return Vector2(0, 0);
		float len = lenth();
		return Vector2(x / len, y / len);
	}
public:
	Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}
	Vector2 operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}
	void operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
	}
	void operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}
	float operator*(const Vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}
	Vector2 operator*(float val) const
	{
		return Vector2(x * val, y * val);
	}
	void operator*=(float val)
	{
		x *= val;
		y *= val;
	}
public:
	float x;
	float y;
};

#endif // ! _VECTOR2_H_
