#pragma once
#include"DamageObject.h"
class Weapon:public DamageObject//½üÕ½ÎäÆ÷
{
public:
	Weapon() {};
	~Weapon() {};
	class collision_rectangle {
	public:
		Vector2 point;
		int width;
		int height;
	};
	virtual void on_updata(int delta) {}
	virtual void on_draw(Camera& camera) {}
	virtual bool player_collision(Vector2 p, float r)
	{
		is_collision=point_in_rec(&p, &rec);
		return is_collision;
	}
	bool point_in_rec(Vector2* v, collision_rectangle* c)
	{
		if (v->x >= c->point.x && v->x <= c->point.x + c->width &&
			v->y >= c->point.y && v->y <= c->point.y + c->height)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
protected:
	collision_rectangle rec;
};
