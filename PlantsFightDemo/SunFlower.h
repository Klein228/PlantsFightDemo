#pragma once
#include"Player.h"
#include"Animation.h"
#include"Timer.h"
#include"Vector2.h"
#include"bullet.h"
#include"SunBullet.h"
#include"SunBulletEx.h"
#include<graphics.h>
extern Camera main_camera;
extern Atlas atlas_sunflower_run_right;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_die_right;
extern Atlas atlas_sunflower_attack_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_die_left;
extern Atlas atlas_sunflower_attack_left;
extern Atlas atlas_sun_text;
class SunFlower : public Player
{
public:

	SunFlower(int id):Player(id)
	{
		this->player_character = playerCharacter::sunflower;
		this->run_speed = 0.35;
		this->img_size.x = atlas_sunflower_idle_right.get_img_at(0)->getwidth();
		this->img_size.y = atlas_sunflower_idle_right.get_img_at(0)->getheight();

		animation_player_idle_left.set_atlas(&atlas_sunflower_idle_left);
		animation_player_idle_left.set_interval(100);
		animation_player_idle_left.set_loop(true);
		animation_player_idle_right.set_atlas(&atlas_sunflower_idle_right);
		animation_player_idle_right.set_interval(100);
		animation_player_idle_right.set_loop(true);

		animation_player_run_left.set_atlas(&atlas_sunflower_run_left);
		animation_player_run_left.set_interval(100);
		animation_player_run_left.set_loop(true);
		animation_player_run_right.set_atlas(&atlas_sunflower_run_right);
		animation_player_run_right.set_interval(100);
		animation_player_run_right.set_loop(true);

		animation_player_die_left.set_atlas(&atlas_sunflower_die_left);
		animation_player_die_left.set_interval(1000);
		animation_player_die_left.set_loop(false);
		animation_player_die_left.set_callback([&]() {
			call_back();
			});
		animation_player_die_right.set_atlas(&atlas_sunflower_die_right);
		animation_player_die_right.set_interval(1000);
		animation_player_die_right.set_loop(false);
		animation_player_die_right.set_callback([&]() {
			call_back();
			});

		animation_player_attack_left.set_atlas(&atlas_sunflower_attack_left);
		animation_player_attack_left.set_interval(50);
		animation_player_attack_left.set_loop(false);
		animation_player_attack_left.set_callback([&]() {
			if (state == playerState::attack)state = playerState::idle;
			});
		animation_player_attack_right.set_atlas(&atlas_sunflower_attack_right);
		animation_player_attack_right.set_interval(50);
		animation_player_attack_right.set_loop(false);
		animation_player_attack_right.set_callback([&]() {
			if (state == playerState::attack)state = playerState::idle;
			});

		animation_sun_text.set_atlas(&atlas_sun_text);
		animation_sun_text.set_interval(50);
		animation_sun_text.set_loop(false);

		//普通攻击计时器初始化
		timer_attack.set_one_shot(false);
		timer_attack.set_wait_time(500);//攻击间隔时间ms
		timer_attack.set_callback([&]() {
			can_attack = true;
			});
		//粒子计时器初始化
		timer_run_effect.set_one_shot(false);
		timer_run_effect.set_wait_time(200);//粒子产生间隔时间
		timer_run_effect.set_callback([&]() {
			can_generate_run_effect = true;
			});
	}
	~SunFlower()
	{
		on_exit();
	}

	void on_input(const ExMessage& msg)
	{
		Player::on_input(msg);
	}
	void on_updata(int delta)
	{
		//死亡状态检测
		if (blood <= 0)
		{
			state = playerState::die;
			animation_player_die_left.on_updata(delta);
			animation_player_die_right.on_updata(delta);
			return;
		}
		//移动状态检测
		if (left_key_down)
		{
			if (right_key_down)
			{
				speed_vector.x = 0;
				if(state!=playerState::attack)state = playerState::idle;
			}
			else
			{
				speed_vector.x = 0 - run_speed;
				if (state != playerState::attack)
				{
					state = playerState::run;
					if (is_collision && can_generate_run_effect) {
						list_particle_effects.push_back(new RunParticle(get_pos_center().x, get_pos_center().y, img_size.y / 2));
						can_generate_run_effect = false;
						timer_run_effect.restart();
					}
				}
			}
		}
		else
		{
			if (right_key_down)
			{
				speed_vector.x = run_speed;
				if (state != playerState::attack)state = playerState::run;
				if (is_collision && can_generate_run_effect) {
					list_particle_effects.push_back(new RunParticle(get_pos_center().x, get_pos_center().y, img_size.y / 2));
					can_generate_run_effect = false;
					timer_run_effect.restart();
				}
			}
			else
			{
				speed_vector.x = 0;
				if (state != playerState::attack)state = playerState::idle;
			}
		}
		//碰撞检测
		move_collision(delta);
		//跳跃按键处理
		if (up_key_down)
		{
			speed_vector.y = 0 - jump_speed;
			up_key_down = false;
			list_particle_effects.push_back(new JumpParticle(get_pos_center().x, get_pos_center().y, img_size.y / 2));
		}
		//子弹列表处理
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->on_updata(delta);
		}
		updata_bullet_list();
		//粒子状态更新
		for (size_t i = 0; i < list_particle_effects.size(); i++)
		{
			list_particle_effects[i]->on_updata(delta);
		}
		updata_particle_list();
		timer_run_effect.on_updata(delta);
		//攻击状态
		timer_attack.on_updata(delta);
		if (attack_key_down && can_attack)
		{
			bullets.push_back(new SunBullet(pos_player.x, pos_player.y, facing_right));
			attack_key_down = false;
			can_attack = false;
			timer_attack.restart();
		}
		//技能
		if (ex_key_down && energy == 100)
		{
			main_camera.shake(20, 200);
			mciSendString(L"play sun_text from 0", NULL, 0, NULL);
			energy = 0;
			bullets.push_back(new SunBulletEx(pos_enemy_player.x, pos_enemy_player.y));
			ex_key_down = false;
			state = playerState::attack;
			animation_player_attack_left.reset();
			animation_player_attack_right.reset();
			animation_sun_text.reset();
		}
		//状态动画更新
		if (facing_right)
		{
			switch (state)
			{
			case Player::playerState::idle:
				animation_player_idle_right.on_updata(delta);
				break;
			case Player::playerState::run:
				animation_player_run_right.on_updata(delta);
				break;
			case Player::playerState::die:
				animation_player_die_right.on_updata(delta);
				break;
			case Player::playerState::attack:
				animation_player_attack_right.on_updata(delta);
				animation_sun_text.on_updata(delta);
				break;
			default:
				break;
			}
		}
		else
		{
			switch (state)
			{
			case Player::playerState::idle:
				animation_player_idle_left.on_updata(delta);
				break;
			case Player::playerState::run:
				animation_player_run_left.on_updata(delta);
				break;
			case Player::playerState::die:
				animation_player_die_left.on_updata(delta);
				break;
			case Player::playerState::attack:
				animation_player_attack_left.on_updata(delta);
				animation_sun_text.on_updata(delta);
				break;
			default:
				break;
			}
		}

	}
	void on_draw(Camera &camera)
	{
		Player::on_draw(camera);
		if (state == playerState::attack)animation_sun_text.on_draw(pos_player.x-50,pos_player.y-50);
	}


private:

	Animation animation_sun_text;
	Timer timer_run_effect;//跑动粒子产生计时器
	bool can_generate_run_effect = true;

	Timer timer_attack;//普通攻击间隔计时器
	bool can_attack=true;//能进行攻击标志
};
