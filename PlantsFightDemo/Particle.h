#pragma once
#include<graphics.h>
#include"Camera.h"
#include"Animation.h"
class Particle//Á£×ÓÏµÍ³
{
public:
	Particle(){}
	~Particle(){}
	virtual void  on_updata(int delta){}
	virtual void on_draw(Camera& camera){}
	bool check_is_over()
	{
		return is_over;
	}
protected:
	bool is_over=false;
};