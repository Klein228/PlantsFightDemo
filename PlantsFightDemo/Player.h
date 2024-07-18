#pragma once
#include<graphics.h>
#include"Camera.h"
#include"Vector2.h"
#include"Animation.h"
#include"Platform.h"
extern std::vector<Platform> list_platform;
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
					if (is_collision)
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
					if (is_collision)up_key_down = true;
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
					if (!is_collision)up_key_down = false;
					break;
				case 'A':
					left_key_down = false;
					break;
				case 'D':
					right_key_down = false;
					break;
				case 'F':
					//attack_key_down = false;
				case 'G':
					//ex_key_down = false;
					break;
				default:
					break;
				}
				break;
			case 2:
				switch (msg.vkcode)
				{
				case VK_UP:
					if(!is_collision)up_key_down = false;
					break;
				case VK_LEFT:
					left_key_down = false;
					break;
				case VK_RIGHT:
					right_key_down = false;
					break;
				case '?':
					//attack_key_down = false;
				case '>':
					//ex_key_down = false;
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
		//¸üÐÂÍæ¼Ò×´Ì¬,×´Ì¬×°»»
		if (left_key_down)
		{
			if (right_key_down)
			{
				speed_vector.x = 0;
				state = playerState::idle;
			}
			else
			{
				speed_vector.x = 0 - run_speed;
				state = playerState::run;
			}
		}
		else
		{
			if (right_key_down)
			{
				speed_vector.x = run_speed;
				state = playerState::run;
			}
			else
			{
				speed_vector.x = 0;
				state = playerState::idle;
			}
		}
		//¹¥»÷×´Ì¬
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
				//´ý¼ÓÈë
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
				//´ý¼ÓÈë
				break;
			default:
				break;
			}
		}

		//Åö×²¼ì²â ÌøÔ¾
		move_collision(delta);
		if (up_key_down)
		{
			speed_vector.y = 0 - jump_speed;
			up_key_down = false;
		}
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
				//´ý¼ÓÈë
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
				//´ý¼ÓÈë
				break;
			default:
				break;
			}
		}
	};
	virtual void move_collision(int delta)
	{
		pos_player.x += speed_vector.x * delta;
		auto temp = pos_player.y;
		speed_vector.y += gravity * delta;
		pos_player.y += speed_vector.y * delta;
		if (speed_vector.y > 0)
		{
			for (size_t i = 0; i < list_platform.size(); i++)
			{
				if (temp+img_size.y<=list_platform[i].shape.y && pos_player.y+img_size.y>=list_platform[i].shape.y&&
					pos_player.x+img_size.x-list_platform[i].shape.x_begin<=list_platform[i].shape.x_end- list_platform[i].shape.x_begin+img_size.x&&
					pos_player.x + img_size.x - list_platform[i].shape.x_begin>=0)
				{
					pos_player.y = list_platform[i].shape.y-img_size.y;
					speed_vector.y = 0;
					is_collision=true;
					return;
				}
			}
		}
		is_collision=false;
	}
	virtual void init_pos()
	{
		if (id == 1)pos_player = { 100,0 };
		else pos_player = { 1000,0 };
	}
protected:
	int id=1;
	Vector2 speed_vector = { 0.0,0.0 };
	POINT img_size = { 0,0 };
	float gravity = 1e-3;
	float run_speed=0.1;
	float jump_speed = 0.65;
	bool is_collision = false;
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
