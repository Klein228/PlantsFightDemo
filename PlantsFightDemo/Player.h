#pragma once
#include<graphics.h>
#include"Camera.h"
#include"Vector2.h"
#include"Animation.h"
#include"Platform.h"
#include"bullet.h"
#include"Particle.h"
#include"RunParticle.h"
#include"JumpParticle.h"
extern Camera main_camera;
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
	enum class playerCharacter
	{
		sunflower,
		peashoooter
	};
public:
	Player(int id)
	{
		set_id(id);
		init_pos();
	}
	~Player()
	{
		on_exit();
	}
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
					if(state!=playerState::die)facing_right = false;
					break;
				case 'D':
					right_key_down = true;
					if (state != playerState::die)facing_right = true;
					break;
				case 'F':
					attack_key_down = true;
					break;
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
					if (state != playerState::die)facing_right = false;
					break;
				case VK_RIGHT:
					right_key_down = true;
					if (state != playerState::die)facing_right = true;
					break;
					//">"
				case 190:
					attack_key_down = true;
					break;
					//"?"
				case 191:
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
					attack_key_down = false;
					break;
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
					if(!is_collision)up_key_down = false;
					break;
				case VK_LEFT:
					left_key_down = false;
					break;
				case VK_RIGHT:
					right_key_down = false;
					break;
				case '?':
					attack_key_down = false;
					break;
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
		//�������״̬,״̬װ��
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
		//����״̬
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
				//������
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
				//������
				break;
			default:
				break;
			}
		}

		//ƽ̨��ײ��� ��Ծ
		move_collision(delta);
		if (up_key_down)
		{
			speed_vector.y = 0 - jump_speed;
			up_key_down = false;
		}
	};
	virtual void on_draw(Camera& camera) 
	{
		for (size_t i = 0; i < list_particle_effects.size(); i++)
		{
			list_particle_effects[i]->on_draw(camera);
		}
		if (is_debug)
		{
			circle(get_pos_center().x, get_pos_center().y, radius_collision);
		}
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
				animation_player_attack_right.on_draw(pos_player.x, pos_player.y);
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
				animation_player_attack_left.on_draw(pos_player.x, pos_player.y);
				break;
			default:
				break;
			}
		}
		
	};
	virtual void bullet_draw(Camera& camera)//���������Ⱦ��������ӵ���Ⱦ֮ǰ,�ʷ������������ӵ�����Ⱦ����
	{
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->on_draw(camera);
		}
	}
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
		if (id == 1)
		{
			facing_right = true;
			pos_player = { 100,0 };
		}
		else
		{
			facing_right = false;
			pos_player = { 1000,0 };
		}
	}
	virtual std::vector<Bullet*>* get_bullets()
	{
		return &bullets;
	}
	virtual void bullets_collision(std::vector<Bullet*>* blts)//�����ⲿ�ӵ���ײ�߼�
	{
		for (size_t i = 0; i < blts->size(); i++)
		{
			if (blts->at(i)->get_is_collision())continue;
			Vector2 pos = blts->at(i)->get_center_pos();
			float r = blts->at(i)->get_radius_collission();
			Vector2 pos_p = get_pos_center();
			float r_p = get_radius_collision();
			float distance = get_distance(pos, pos_p);

			if (distance <= r + r_p)
			{
				//�����ӵ���ը��Ч 
				if (!blts->at(i)->get_is_collision())
				{
					switch (blts->at(i)->bullet_type)
					{
					case Bullet::peabullet:
						mciSendString(L"play pea_break_1 from 0", NULL, 0, NULL);
						break;
					case Bullet::sunbullet:
						mciSendString(L"play sun_explode from 0", NULL, 0, NULL);
						break;
					case Bullet::sunbulletex:
						mciSendString(L"play sun_explode_ex from 0", NULL, 0, NULL);
						break;
					default:
						break;
					}
				}

				blts->at(i)->set_is_collision(true);
				blood = (blood - blts->at(i)->get_bullet_damage() > 0) ? blood - blts->at(i)->get_bullet_damage() : 0;
				//player hurt()
			}
		}
	}
	void on_exit()//�����ڴ�
	{
		for (size_t i = 0; i < bullets.size(); i++)
		{
			delete bullets[i];
		}
		for (size_t i = 0; i < list_particle_effects.size(); i++)
		{
			delete list_particle_effects[i];
		}
	}
	void set_radius_collision(float f)
	{
		radius_collision = f;
	}
	float get_radius_collision()
	{
		return radius_collision;
	}
	Vector2 get_pos_center()//��ȡ�������λ��
	{
		return { pos_player.x + img_size.x / 2,pos_player.y + img_size.y / 2 };
	}
	void updata_bullet_list()//���������ӵ��б�
	{
		int i = 0;
		int j = bullets.size() - 1;
		while (i<=j)
		{
			if (bullets[i]->get_is_collision()&&!bullets[i]->get_is_culculated())
			{
				energy = (energy + bullets[i]->get_energy() > 100) ? 100 : energy + bullets[i]->get_energy();
				if (bullets[i]->bullet_type == Bullet::sunbullet)main_camera.shake(10, 100);
				bullets[i]->set_is_culculated(true);
			}
			if (bullets[i]->get_is_out_window() || bullets[i]->get_is_exploded_over())
			{
				auto temp = bullets[i];
				bullets[i] = bullets[j];
				delete temp;
				bullets.pop_back();
				j--;
			}
			else
			{
				i++;
			}
		}
	}
	void updata_particle_list()//�������������б�
	{
		int i = 0;
		int j = list_particle_effects.size() - 1;
		while (i <= j)
		{
			if (list_particle_effects[i]->check_is_over())
			{
				auto temp = list_particle_effects[i];
				list_particle_effects[i] = list_particle_effects[j];
				delete temp;
				list_particle_effects.pop_back();
				j--;
			}
			else
			{
				i++;
			}
		}
	}
	void set_enemy_player_center_pos(Vector2 v)
	{
		pos_enemy_player = v;
	}
	int get_blood()
	{
		return blood;
	}
	void set_blood(int b)
	{
		blood = b>100?100:b;
	}
	int get_energy()
	{
		return energy;
	}
	void set_energy(int e)
	{
		energy = e>100?100:e;
	}
	playerCharacter get_player_type()
	{
		return player_character;
	}
	void set_call_back(std::function<void()> fun)
	{
		this->call_back = fun;
	}
protected:
	int id=1;//���id
	Vector2 speed_vector = { 0.0,0.0 };//�ٶ�
	POINT img_size = { 0,0 };//���ͼƬ��С
	float gravity = 1e-3;//��������
	float run_speed=0.1;//�ƶ��ٶ�
	float jump_speed = 0.65;//��Ծ��ʼ�ٶ�
	bool is_collision = false;//�Ƿ���ײ��ƽ̨
	playerState state = playerState::idle;//��ǰ����״̬
	Vector2 pos_player = { 0,0 };//���ͼƬ��Ⱦλ��
	Vector2 pos_enemy_player = { 0,0 };//�ж��������λ��
	Animation animation_player_run_left;
	Animation animation_player_run_right;
	Animation animation_player_idle_left;
	Animation animation_player_idle_right;
	Animation animation_player_die_left;
	Animation animation_player_die_right;
	Animation animation_player_attack_left;
	Animation animation_player_attack_right;
	bool facing_right = true;//�Ƿ�����
	//������־
	bool left_key_down=false;
	bool right_key_down = false;
	bool up_key_down = false;
	bool attack_key_down = false;
	bool ex_key_down = false;
	playerCharacter player_character;//�������
	std::vector<Bullet*> bullets;//��ҷ������ӵ�
	float radius_collision = 30;//���ӵ���ײ���뾶

	int blood=100;
	int energy=0;
	std::function<void()> call_back;//�����������
	std::vector<Particle*> list_particle_effects;//�����б�
};
