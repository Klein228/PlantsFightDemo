#pragma once
#include"Particle.h"
extern Atlas atlas_jump_effect;

class JumpParticle :public Particle
{
public:
	JumpParticle(int center_x, int center_y, int half_height)
	{
		mciSendString(L"play jump from 0", NULL, 0, NULL);
		size_jump_effect.x = atlas_jump_effect.get_img_at(0)->getwidth();
		size_jump_effect.y = atlas_jump_effect.get_img_at(0)->getheight();
		pos_jump_effect.x = center_x - size_jump_effect.x / 2;
		pos_jump_effect.y = center_y + half_height - size_jump_effect.y;
		animation_jump_effect.set_atlas(&atlas_jump_effect);
		animation_jump_effect.set_interval(100);
		animation_jump_effect.set_loop(false);
		animation_jump_effect.set_callback([&]() {
			is_over = true;
			});
	}
	~JumpParticle() {}
	void on_updata(int delta)
	{
		animation_jump_effect.on_updata(delta);
	}
	void on_draw(Camera& camera)
	{
		animation_jump_effect.on_draw(pos_jump_effect.x, pos_jump_effect.y);
	}

private:
	Animation animation_jump_effect;
	POINT pos_jump_effect;
	POINT size_jump_effect;
};

