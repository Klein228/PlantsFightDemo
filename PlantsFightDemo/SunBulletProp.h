#pragma once
#include"SunBullet.h"
class SunBulletProp:public SunBullet
{
public:
	SunBulletProp(int x, int y):SunBullet(x,y,true)
	{
		speed_x = 0;
		speed.x = 0;
		speed.y = 0.5;
		speed_y = 0.5;
		gravity_sunbullet = 0;
	};
	~SunBulletProp() {};

private:

};


