#pragma once
#include"Player.h"
#include"Animation.h"
#include"Timer.h"
#include"Vector2.h"
#include"bullet.h"
#include"SunBullet.h"
#include"SunBulletEx.h"
#include<graphics.h>
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
		animation_player_die_left.set_interval(100);
		animation_player_die_left.set_loop(true);
		animation_player_die_right.set_atlas(&atlas_sunflower_die_right);
		animation_player_die_right.set_interval(100);
		animation_player_die_right.set_loop(true);

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

		//��ͨ������ʱ����ʼ��
		timer_attack.set_one_shot(false);
		timer_attack.set_wait_time(1000);//�������ʱ��ms
		timer_attack.set_callback([&]() {
			can_attack = true;
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
		//Player::on_updata(delta);
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
				if (state != playerState::attack)state = playerState::run;
			}
		}
		else
		{
			if (right_key_down)
			{
				speed_vector.x = run_speed;
				if (state != playerState::attack)state = playerState::run;
			}
			else
			{
				speed_vector.x = 0;
				if (state != playerState::attack)state = playerState::idle;
			}
		}
		//����״̬
		timer_attack.on_updata(delta);
		if (attack_key_down&&can_attack)
		{
			bullets.push_back(new SunBullet(pos_player.x, pos_player.y, facing_right));
			attack_key_down = false;
			can_attack = false;
			timer_attack.restart();
		}
		
		//����
		if (ex_key_down)
		{
			bullets.push_back(new SunBulletEx(pos_enemy_player.x, pos_enemy_player.y));
			ex_key_down = false;
			state = playerState::attack;
			animation_player_attack_left.reset();
			animation_player_attack_right.reset();
			animation_sun_text.reset();
		}
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

		//��ײ��� ��Ծ
		move_collision(delta);
		if (up_key_down)
		{
			speed_vector.y = 0 - jump_speed;
			up_key_down = false;
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->on_updata(delta);
		}
		updata_bullet_list();
	}
	void on_draw(Camera &camera)
	{
		Player::on_draw(camera);
		if (state == playerState::attack)animation_sun_text.on_draw(pos_player.x-50,pos_player.y-50);
	}
	void bullet_draw(Camera& camera)
	{
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->on_draw(camera);
		}
	}
	void on_exit()//�����ڴ�
	{
		for (size_t i = 0; i < bullets.size(); i++)
		{
			delete bullets[i];
		}
	}

private:
	Animation animation_sun_text;
	Timer timer_attack;//��ͨ���������ʱ��
	bool can_attack=true;//�ܽ��й�����־
};
