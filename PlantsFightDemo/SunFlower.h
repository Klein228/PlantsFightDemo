#pragma once
#include"Player.h"
#include"Animation.h"
#include"Timer.h"
#include"Vector2.h"
#include<graphics.h>
extern Atlas atlas_sunflower_run;
extern Atlas atlas_sunflower_idle;
extern Atlas atlas_sunflower_die;
extern Atlas atlas_sunflower_attack;
class SunFlower : public Player
{
public:
	enum Action
	{
		idle,
		run,
		attack,
		die
	};
	SunFlower()
	{
		on_enter();
	}
	~SunFlower(){}
	void on_enter()
	{
		animation_idle.set_atlas(&atlas_sunflower_idle);
		animation_idle.set_interval(100);
		animation_idle.set_loop(true);
		animation_attack.set_atlas(&atlas_sunflower_attack);
		animation_attack.set_interval(100);
		animation_attack.set_loop(false);
		animation_run.set_atlas(&atlas_sunflower_run);
		animation_run.set_interval(100);
		animation_run.set_loop(true);
		animation_die.set_atlas(&atlas_sunflower_die);
		animation_die.set_interval(200);
		animation_die.set_loop(false);
		animation_die.set_callback([&]() {
			//on_exit();
			});
	}
	void on_input(ExMessage& msg)
	{

	}
	void on_updata(int delta)
	{
		switch (action)
		{
		case SunFlower::idle:
			animation_idle.on_updata(delta);
			break;
		case SunFlower::run:
			animation_run.on_updata(delta);
			break;
		case SunFlower::attack:
			animation_attack.on_updata(delta);
			break;
		case SunFlower::die:
			animation_die.on_updata(delta);
			break;
		default:
			break;
		}
	}
	void on_draw()
	{
		switch (action)
		{
		case SunFlower::idle:
			animation_idle.on_draw(location.x,location.y);
			break;
		case SunFlower::run:
			animation_run.on_draw(location.x, location.y);
			break;
		case SunFlower::attack:
			animation_attack.on_draw(location.x, location.y);
			break;
		case SunFlower::die:
			animation_die.on_draw(location.x, location.y);
			break;
		default:
			break;
		}
	}
	void on_exit()
	{
		this->~SunFlower();
	}
	void setLocation(Vector2 v)
	{
		location.x = v.x;
		location.y = v.y;
	}
private:
	Action action = idle;
	Animation animation_idle;
	Animation animation_run;
	Animation animation_die;
	Animation animation_attack;
	Vector2 location = {0,0};
	Timer timer_run;
	Timer timer_idle;
	Timer timer_die;
	Timer timer_attack;
};
