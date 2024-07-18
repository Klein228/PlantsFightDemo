#pragma once
#include"bullet.h"
#include"Camera.h"
extern Atlas atlas_sunflower_bullet;
class SunBullet:public Bullet
{
public:
	SunBullet(int x,int y,bool facing_right)
	{
		pos_bullet.x = x;
		pos_bullet.y = y;
		
		animation_bullet.set_atlas(&atlas_sunflower_bullet);
		animation_bullet.set_loop(true);
		animation_bullet.set_interval(100);

		if (facing_right)
		{
			bullet_speed.x = speed_x;
		}
		else
		{
			bullet_speed.x = -speed_x;
		}
		bullet_speed.y = speed_y;
	}
	~SunBullet()
	{

	}
	void on_updata(int delta)
	{
		animation_bullet.on_updata(delta);
		bullet_speed.y += gravity_sunbullet * delta;
		pos_bullet.x += bullet_speed.x * delta;
		pos_bullet.y += bullet_speed.y * delta;
	}
	void on_draw(Camera& camera)
	{
		animation_bullet.on_draw(pos_bullet.x,pos_bullet.y);
	}


	
private:
	Vector2 bullet_speed = { 0,0 };
	float gravity_sunbullet = 5e-4;
	float speed_x = 0.2;
	float speed_y = -0.2;
};

