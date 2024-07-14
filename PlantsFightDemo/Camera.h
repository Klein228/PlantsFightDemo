#pragma once
#include"Vector2.h"
class Camera
{
public:
	Camera(){}
	~Camera(){}
	const Vector2& get_position() const
	{
		return position;
	}
	void reset()
	{
		position.x = 0;
		position.y = 0;
	}
	void on_updata(int delta)
	{
		const Vector2 speed = { -0.25f,0 };
		position += speed*(float)delta;
	}
private:
	Vector2 position = {0,0};
};