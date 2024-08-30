#pragma once
#include"Weapon.h"
#include"Timer.h"
extern bool  is_debug;
class NinjaSword:public Weapon
{
public:
	NinjaSword(Vector2 pos) {
		rec.point = pos;
		rec.height = 100;
		rec.width = 50;
		attack_timer.set_callback([&] {
			is_over = true;
			});
		attack_timer.set_one_shot(true);
		attack_timer.set_wait_time(200);
	};
	~NinjaSword() {};
	virtual void on_updata(int delta) {
		attack_timer.on_updata(delta);
	}
	virtual void on_draw(Camera& camera) 
	{
		if (is_debug) {
			rectangle(rec.point.x, rec.point.y, rec.point.x + rec.width, rec.point.y + rec.height);
		}
	}
	virtual bool object_over()
	{
		return is_over||is_collision;
	}
	void set_weapon_wh(POINT p)
	{
		rec.width = p.x;
		rec.height = p.y;
	};
private:
	Timer attack_timer;//攻击后持续时间计时
	bool is_over=false;
};

