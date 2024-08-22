#pragma once
#include"Player.h"
#include"Animation.h"
#include"Timer.h"
#include"PeaBullet.h"
#include"PeaTrackingBullet.h"
extern Camera main_camera;
extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_die_right;
extern Atlas atlas_peashooter_attack_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_die_left;
extern Atlas atlas_peashooter_attack_left;
extern Player *player1;
extern Player *player2;
class PeaShooter:public Player
{
public:
	PeaShooter(int id):Player(id)
	{
		this->player_character = playerCharacter::peashoooter;
		this->run_speed = 0.35;
		this->img_size.x = atlas_peashooter_idle_right.get_img_at(0)->getwidth();
		this->img_size.y = atlas_peashooter_idle_right.get_img_at(0)->getheight();
		animation_player_idle_left.set_atlas(&atlas_peashooter_idle_left);
		animation_player_idle_left.set_interval(100);
		animation_player_idle_left.set_loop(true);
		animation_player_idle_right.set_atlas(&atlas_peashooter_idle_right);
		animation_player_idle_right.set_interval(100);
		animation_player_idle_right.set_loop(true);

		animation_player_run_left.set_atlas(&atlas_peashooter_run_left);
		animation_player_run_left.set_interval(100);
		animation_player_run_left.set_loop(true);
		animation_player_run_right.set_atlas(&atlas_peashooter_run_right);
		animation_player_run_right.set_interval(100);
		animation_player_run_right.set_loop(true);

		animation_player_die_left.set_atlas(&atlas_peashooter_die_left);
		animation_player_die_left.set_interval(1000);
		animation_player_die_left.set_loop(false);
		animation_player_die_left.set_callback([&]() {
			call_back();
			});
		animation_player_die_right.set_atlas(&atlas_peashooter_die_right);
		animation_player_die_right.set_interval(1000);
		animation_player_die_right.set_loop(false);
		animation_player_die_right.set_callback([&]() {
			call_back();
			});


		animation_player_attack_left.set_atlas(&atlas_peashooter_attack_left);
		animation_player_attack_left.set_interval(10);
		animation_player_attack_left.set_loop(true);
		animation_player_attack_right.set_atlas(&atlas_peashooter_attack_right);
		animation_player_attack_right.set_interval(10);
		animation_player_attack_right.set_loop(true);
		//计时器初始化
		timer_ex_peashot.set_one_shot(false);
		timer_ex_peashot.set_wait_time(100);
		timer_ex_peashot.set_callback([&]() {
			if (!super_skill)bullets.push_back(new PeaBullet(pos_player.x + img_size.x / 3, pos_player.y + img_size.y * 1 / 16, facing_right));
			else bullets.push_back(new PeaTrackingBullet(pos_player.x + img_size.x / 3, pos_player.y + img_size.y * 1 / 16, facing_right, this ==player1 ? player2 : player1));
			});
		timer_ex_skill.set_one_shot(false);
		timer_ex_skill.set_wait_time(2000);
		timer_ex_skill.set_callback([&]() {
			timer_ex_skill.restart();
			timer_ex_skill.pause();
			timer_ex_peashot.pause();
			super_skill = false;
			if (state == playerState::attack)state = playerState::idle;
			});
		timer_ex_skill.pause();
		timer_ex_peashot.pause();

		timer_interval_attack.set_one_shot(false);
		timer_interval_attack.set_wait_time(400);
		timer_interval_attack.set_callback([&]() {
			can_attack = true;
			});
		//粒子计时器初始化
		timer_run_effect.set_one_shot(false);
		timer_run_effect.set_wait_time(200);//粒子产生间隔时间
		timer_run_effect.set_callback([&]() {
			can_generate_run_effect = true;
			});
	};
	~PeaShooter() {};

	void on_input(const ExMessage& msg)
	{
	
		Player::on_input(msg);

	}
	void on_updata(int delta)
	{
		//死亡状态检测
		is_player_in_window();
		if (blood <= 0||out_window)
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
				if (state != playerState::attack)state = playerState::idle;
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
		//平台碰撞检测
		move_collision(delta);
		//跳跃按键处理
		if (up_key_down)
		{
			speed_vector.y = 0 - jump_speed;
			up_key_down = false;
			list_particle_effects.push_back(new JumpParticle(get_pos_center().x, get_pos_center().y, img_size.y / 2));
		}
		//子弹更新
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
		timer_interval_attack.on_updata(delta);//攻击间隔更新
		if (attack_key_down&&can_attack)
		{
			mciSendString(L"play pea_shoot_2 from 0", NULL, 0, NULL);
			can_attack = false;
			bullets.push_back(new PeaBullet(pos_player.x + img_size.x / 3, pos_player.y + img_size.y * 1 / 16, facing_right));
			attack_key_down = false;
			timer_interval_attack.restart();
		}
		timer_ex_peashot.on_updata(delta);
		timer_ex_skill.on_updata(delta);
		//技能
		if (energy == 100&&ex_key_down&&state!=playerState::attack)
		{
			if (num_skill_ultra > 0)
			{
				mciSendString(L"play pea_shoot_ex from 0", NULL, 0, NULL);
				super_skill = true;
				energy = 0;
				ex_key_down = false;
				num_skill_ultra--;
				state = playerState::attack;
				timer_ex_peashot.resume();
				timer_ex_skill.resume();
			}
			else
			{
				mciSendString(L"play pea_shoot_ex from 0", NULL, 0, NULL);
				main_camera.shake(10, 2000);
				ex_key_down = false;
				energy = 0;
				state = playerState::attack;
				timer_ex_peashot.resume();
				timer_ex_skill.resume();
			}
				
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
				break;
			default:
				break;
			}
		}


	}
	void on_draw(Camera& camera)
	{
		Player::on_draw(camera);
	}

private:
	Timer timer_ex_skill;//技能持续时长计时器
	Timer timer_ex_peashot;//技能子弹循环产生计时器
	Timer timer_interval_attack;//普通攻击间隔计时器
	bool can_attack = true;//攻击间隔时间是否已过
	Timer timer_run_effect;//跑动粒子产生计时器
	bool can_generate_run_effect = true;
	bool super_skill = false;
};
