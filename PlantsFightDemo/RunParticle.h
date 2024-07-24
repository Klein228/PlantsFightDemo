#pragma once
#include"Particle.h"
extern Atlas atlas_run_effect;

class RunParticle:public Particle
{
public:
	RunParticle(int center_x,int center_y,int half_height)
	{
		size_run_effect.x = atlas_run_effect.get_img_at(0)->getwidth();
		size_run_effect.y = atlas_run_effect.get_img_at(0)->getheight();
		pos_run_effect.x = center_x-size_run_effect.x/2;
		pos_run_effect.y = center_y+half_height-size_run_effect.y;
		animation_run_effect.set_atlas(&atlas_run_effect);
		animation_run_effect.set_interval(100);
		animation_run_effect.set_loop(false);
		animation_run_effect.set_callback([&]() {
			is_over = true;
			});
	}
	~RunParticle(){}
	void on_updata(int delta)
	{
		animation_run_effect.on_updata(delta);
	}
	void on_draw(Camera& camera)
	{
		animation_run_effect.on_draw(pos_run_effect.x,pos_run_effect.y);
	}

private:
	Animation animation_run_effect;
	POINT pos_run_effect;
	POINT size_run_effect;
};

