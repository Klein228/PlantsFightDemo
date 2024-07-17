#pragma once
#include<graphics.h>
#include"Camera.h"
#include"Vector2.h"
#include"Animation.h"
class Player
{
public:
	enum class playerState
	{
		idle,
		run,
		die,
		attack
	};
public:
	Player(){}
	~Player(){}
	virtual void set_id(int id)
	{
		this->id = id;
	}
	virtual void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			switch (id)
			{
			case 1:
				switch (msg.vkcode)
				{
				case 'W':
					up_key_down = true;
					break;
				case 'A':
					left_key_down = true;
					facing_right = false;
					break;
				case 'D':
					right_key_down = true;
					facing_right = true;
					break;
				case 'F':
					attack_key_down = true;
				case 'G':
					ex_key_down = true;
					break;
				default:
					break;
				}
				break;
			case 2:
				switch (msg.vkcode)
				{
				case VK_UP:
					up_key_down = true;
					break;
				case VK_LEFT:
					left_key_down = true;
					facing_right = false;
					break;
				case VK_RIGHT:
					right_key_down = true;
					facing_right = true;
					break;
				case '?':
					attack_key_down = true;
				case '>':
					ex_key_down = true;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		if (msg.message == WM_KEYUP)
		{
			switch (id)
			{
			case 1:
				switch (msg.vkcode)
				{
				case 'W':
					up_key_down = false;
					break;
				case 'A':
					left_key_down = false;
					break;
				case 'D':
					right_key_down = false;
					break;
				case 'F':
					attack_key_down = false;
				case 'G':
					ex_key_down = false;
					break;
				default:
					break;
				}
				break;
			case 2:
				switch (msg.vkcode)
				{
				case VK_UP:
					up_key_down = false;
					break;
				case VK_LEFT:
					left_key_down = false;
					break;
				case VK_RIGHT:
					right_key_down = false;
					break;
				case '?':
					attack_key_down = false;
				case '>':
					ex_key_down = false;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	};
	virtual void on_updata(int delta) 
	{
		if (left_key_down)
		{
			if (right_key_down)speed_vector.x = 0;
			else
			{
				speed_vector.x = 0 - run_speed;
			}
		}
		else
		{
			if (right_key_down)speed_vector.x = run_speed;
			else
			{
				speed_vector.x = 0;
			}
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
				//待加入
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
				//待加入
				break;
			default:
				break;
			}
		}
		//
		pos_player.x += speed_vector.x;
		pos_player.y += speed_vector.y;
	};
	virtual void on_draw(Camera& camera) 
	{
		if (facing_right)
		{
			switch (state)
			{
			case Player::playerState::idle:
				animation_player_idle_right.on_draw(pos_player.x,pos_player.y);
				break;
			case Player::playerState::run:
				animation_player_run_right.on_draw(pos_player.x, pos_player.y);
				break;
			case Player::playerState::die:
				animation_player_die_right.on_draw(pos_player.x, pos_player.y);
				break;
			case Player::playerState::attack:
				//待加入
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
				animation_player_idle_left.on_draw(pos_player.x, pos_player.y);
				break;
			case Player::playerState::run:
				animation_player_run_left.on_draw(pos_player.x, pos_player.y);
				break;
			case Player::playerState::die:
				animation_player_die_left.on_draw(pos_player.x, pos_player.y);
				break;
			case Player::playerState::attack:
				//待加入
				break;
			default:
				break;
			}
		}
	};

protected:
	int id=1;
	Vector2 speed_vector = { 0.0,0.0 };
	int run_speed=10;
	playerState state = playerState::idle;
	Vector2 pos_player = { 0,0 };
	Animation animation_player_run_left;
	Animation animation_player_run_right;
	Animation animation_player_idle_left;
	Animation animation_player_idle_right;
	Animation animation_player_die_left;
	Animation animation_player_die_right;
	Animation animation_player_attack_left;
	Animation animation_player_attack_right;
	bool facing_right = true;

	bool left_key_down=false;
	bool right_key_down = false;
	bool up_key_down = false;
	bool attack_key_down = false;
	bool ex_key_down = false;
};
