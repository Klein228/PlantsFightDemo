#pragma once
#include"graphics.h"
#include"Vector2.h"
#include"Animation.h"
class Bullet
{

public:
	Bullet() {};
	~Bullet() {};
	virtual void on_updata(int delta)
	{}
	virtual void on_draw(Camera& camera)
	{}

	Vector2 pos_bullet = { 0,0 };
protected:
	Animation animation_bullet;
};
