#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector2.h"

class Camera
{
private:
	Vector2 position;
public:
	Camera() = default;
	~Camera() = default;

	void reset()
	{
		position.x = 0;
		position.y = 0;
	}
	void init_camera(float x, float y)
	{
		position = Vector2(x, y);
	}
	const Vector2& get_position() const
	{
		return position;
	}
	void on_update(int delay)
	{
		/*
		* ≤‚ ‘œ‡ª˙
		position.x -= delay;
		*/
	}
};

#endif // !_CAMERA_H_
