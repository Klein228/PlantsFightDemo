#pragma once
#include"Player.h"
#include"Ninja_Sword.h"
extern  Atlas atlas_ninja_run_right;
extern  Atlas atlas_ninja_idle_right;
extern  Atlas atlas_ninja_die_right;
extern  Atlas atlas_ninja_attack_right;
extern  Atlas atlas_ninja_run_left;
extern  Atlas atlas_ninja_idle_left;
extern  Atlas atlas_ninja_die_left;
extern  Atlas atlas_ninja_attack_left;
class Ninja:public Player
{
public:
	Ninja(int id) :Player(id) 
	{
		this->player_character = playerCharacter::ninja;
		this->run_speed = 0.5;
		this->img_size.x = atlas_ninja_idle_right.get_img_at(0)->getwidth();
		this->img_size.y = atlas_ninja_idle_right.get_img_at(0)->getheight();
		weapon_wh.x = 50;
		weapon_wh.y = 100;
		animation_player_idle_left.set_atlas(&atlas_ninja_idle_left);
		animation_player_idle_left.set_interval(100);
		animation_player_idle_left.set_loop(true);
		animation_player_idle_right.set_atlas(&atlas_ninja_idle_right);
		animation_player_idle_right.set_interval(100);
		animation_player_idle_right.set_loop(true);

		animation_player_run_left.set_atlas(&atlas_ninja_run_left);
		animation_player_run_left.set_interval(100);
		animation_player_run_left.set_loop(true);
		animation_player_run_right.set_atlas(&atlas_ninja_run_right);
		animation_player_run_right.set_interval(100);
		animation_player_run_right.set_loop(true);

		animation_player_die_left.set_atlas(&atlas_ninja_die_left);
		animation_player_die_left.set_interval(1000);
		animation_player_die_left.set_loop(false);
		animation_player_die_left.set_callback([&]() {
			call_back();
			});
		animation_player_die_right.set_atlas(&atlas_ninja_die_right);
		animation_player_die_right.set_interval(1000);
		animation_player_die_right.set_loop(false);
		animation_player_die_right.set_callback([&]() {
			call_back();
			});

		animation_player_attack_left.set_atlas(&atlas_ninja_attack_left);
		animation_player_attack_left.set_interval(50);
		animation_player_attack_left.set_loop(false);
		animation_player_attack_left.set_callback([&]() {
			if (state == playerState::attack)state = playerState::idle;
			});
		animation_player_attack_right.set_atlas(&atlas_ninja_attack_right);
		animation_player_attack_right.set_interval(50);
		animation_player_attack_right.set_loop(false);
		animation_player_attack_right.set_callback([&]() {
			if (state == playerState::attack)state = playerState::idle;
			});
		animation_player_normal_attack_left.set_atlas(&atlas_ninja_attack_left);
		animation_player_normal_attack_left.set_interval(20);
		animation_player_normal_attack_left.set_loop(true);
		animation_player_normal_attack_left.set_callback([&]() {
			if (state == playerState::normal_attack)state = playerState::idle;
			});
		animation_player_normal_attack_right.set_atlas(&atlas_ninja_attack_right);
		animation_player_normal_attack_right.set_interval(20);
		animation_player_normal_attack_right.set_loop(true);
		animation_player_normal_attack_right.set_callback([&]() {
			if (state == playerState::normal_attack)state = playerState::idle;
			});
		//普通攻击计时器初始化
		timer_interval_attack.set_one_shot(false);
		timer_interval_attack.set_wait_time(500);//攻击间隔时间ms
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
	~Ninja()
	{
		on_exit();
	};
	void on_input(ExMessage& msg)
	{
		Player::on_input(msg);
	}
	void on_updata(int delta)
	{
		Player::on_updata(delta);
		//攻击状态
		timer_interval_attack.on_updata(delta);
		if (attack_key_down && can_attack)
		{
			//bullets.push_back(new SunBullet(pos_player.x, pos_player.y, facing_right));
			Vector2 rect_p = pos_player;
			if (!facing_right)rect_p.x -= weapon_wh.x;
			else rect_p.x += img_size.x;
			damage_objects.push_back(new NinjaSword(rect_p));
			attack_key_down = false;
			can_attack = false;
			state = playerState::normal_attack;
			timer_interval_attack.restart();
		}
		//技能
		if (ex_key_down && energy == 100)
		{
			if (num_skill_ultra > 0)
			{
				mciSendString(L"play sun_text from 0", NULL, 0, NULL);
				energy = 0;
				num_skill_ultra--;
				ex_key_down = false;
				state = playerState::attack;
				animation_player_attack_left.reset();
				animation_player_attack_right.reset();
			}
			else
			{
				main_camera.shake(20, 200);
				mciSendString(L"play sun_text from 0", NULL, 0, NULL);
				energy = 0;
				ex_key_down = false;
				state = playerState::attack;
				animation_player_attack_left.reset();
				animation_player_attack_right.reset();
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
				//animation_player_attack_right.on_updata(delta);
				break;
			case Player::playerState::normal_attack:
				animation_player_normal_attack_right.on_updata(delta);
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
				//animation_player_attack_left.on_updata(delta);
				break;
			case Player::playerState::normal_attack:
				animation_player_normal_attack_left.on_updata(delta);
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
	POINT weapon_wh;
};
