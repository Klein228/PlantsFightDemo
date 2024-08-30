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
#include"DamageObject.h"
#include"Weapon.h"

extern Camera main_camera;
extern const POINT window_size;
extern std::vector<Platform> list_platform;
class Player
{
public:
	enum class playerState
	{
		idle,
		run,
		die,
		attack,
		normal_attack
	};
	enum class playerCharacter
	{
		sunflower,
		peashoooter,
		ninja
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
		is_player_in_window();
		//����״̬���
		if (blood <= 0 || out_window)
		{
			state = playerState::die;
			animation_player_die_left.on_updata(delta);
			animation_player_die_right.on_updata(delta);
			return;
		}
		//�ƶ�״̬���
		if (left_key_down)
		{
			if (right_key_down)
			{
				speed_vector.x = 0;
				if (state != playerState::attack&& state != playerState::normal_attack)state = playerState::idle;
			}
			else
			{
				speed_vector.x = 0 - run_speed;
				if (state != playerState::attack&& state != playerState::normal_attack)
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
				if (state != playerState::attack && state != playerState::normal_attack)state = playerState::run;
				if (is_collision && can_generate_run_effect) {
					list_particle_effects.push_back(new RunParticle(get_pos_center().x, get_pos_center().y, img_size.y / 2));
					can_generate_run_effect = false;
					timer_run_effect.restart();
				}
			}
			else
			{
				speed_vector.x = 0;
				if (state != playerState::attack && state != playerState::normal_attack)state = playerState::idle;
			}
		}
		//��ײ���
		move_collision(delta);
		//��Ծ��������
		if (up_key_down)
		{
			speed_vector.y = 0 - jump_speed;
			up_key_down = false;
			list_particle_effects.push_back(new JumpParticle(get_pos_center().x, get_pos_center().y, img_size.y / 2));
		}
		//�ӵ��б���
		for (size_t i = 0; i < damage_objects.size(); i++)
		{
			damage_objects[i]->on_updata(delta);
		}
		updata_damage_objects_list();
		//����״̬����
		for (size_t i = 0; i < list_particle_effects.size(); i++)
		{
			list_particle_effects[i]->on_updata(delta);
		}
		updata_particle_list();
		timer_run_effect.on_updata(delta);
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
			case Player::playerState::normal_attack:
				animation_player_normal_attack_right.on_draw(pos_player.x, pos_player.y);
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
			case Player::playerState::normal_attack:
				animation_player_normal_attack_left.on_draw(pos_player.x, pos_player.y);
				break;
			default:
				break;
			}
		}
		
	};
	virtual void damage_objects_draw(Camera& camera)//���������Ⱦ��������ӵ���Ⱦ֮ǰ,�ʷ������������ӵ�����Ⱦ����
	{
		for (size_t i = 0; i < damage_objects.size(); i++)
		{
			damage_objects[i]->on_draw(camera);
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
			pos_player = { 280,0 };
		}
		else
		{
			facing_right = false;
			pos_player = { 1000,0 };
		}
	}
	virtual std::vector<DamageObject*>* get_damage_objects()
	{
		return &damage_objects;
	}
	//virtual void bullets_collision(std::vector<Bullet*>* blts)//�����ⲿ�ӵ���ײ�߼�
	//{
	//	for (size_t i = 0; i < blts->size(); i++)
	//	{
	//		if (blts->at(i)->get_is_collision())continue;
	//		Vector2 pos = blts->at(i)->get_center_pos();
	//		float r = blts->at(i)->get_radius_collission();
	//		Vector2 pos_p = get_pos_center();
	//		float r_p = get_radius_collision();
	//		float distance = get_distance(pos, pos_p);
	//		if (distance <= r + r_p)
	//		{
	//			//�����ӵ���ը��Ч 
	//			if (!blts->at(i)->get_is_collision())
	//			{
	//				switch (blts->at(i)->bullet_type)
	//				{
	//				case Bullet::peabullet:
	//					mciSendString(L"play pea_break_1 from 0", NULL, 0, NULL);
	//					break;
	//				case Bullet::sunbullet:
	//					mciSendString(L"play sun_explode from 0", NULL, 0, NULL);
	//					break;
	//				case Bullet::sunbulletex:
	//					mciSendString(L"play sun_explode_ex from 0", NULL, 0, NULL);
	//					break;
	//				default:
	//					break;
	//				}
	//			}
	//			blts->at(i)->set_is_collision(true);
	//			blood = (blood - blts->at(i)->get_bullet_damage() > 0) ? blood - blts->at(i)->get_bullet_damage() : 0;
	//			//player hurt()
	//		}
	//	}
	//}
	virtual void damage_objects_collision(std::vector<DamageObject*>* d_objects)
	{
		for (size_t i = 0; i < d_objects->size(); i++)
		{
			bool collision=d_objects->at(i)->player_collision(get_pos_center(),get_radius_collision());
			if (collision)
			{
				d_objects->at(i)->play_collision_music();
				d_objects->at(i)->set_is_collision(true);
				blood = (blood - d_objects->at(i)->get_damage() > 0) ? blood - d_objects->at(i)->get_damage() : 0;
			}
		}
	}
	void on_exit()//�����ڴ�
	{
		for (size_t i = 0; i < damage_objects.size(); i++)
		{
			delete damage_objects[i];
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

	void updata_damage_objects_list()//���������б�
	{
		int i = 0;
		int j = damage_objects.size() - 1;
		while (i <= j)
		{
			if (damage_objects[i]->get_is_collision() && !damage_objects[i]->get_is_culculated())
			{
				energy = (energy + damage_objects[i]->get_energy() > 100) ? 100 : energy + damage_objects[i]->get_energy();
				if (damage_objects[i]->bullet_type == Bullet::sunbullet)main_camera.shake(10, 100);
				damage_objects[i]->set_is_culculated(true);
			}
			if (damage_objects[i]->object_over())
			{
				auto temp = damage_objects[i];
				damage_objects[i] = damage_objects[j];
				delete temp;
				damage_objects.pop_back();
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
	void is_player_in_window()
	{
		if (pos_player.y >= window_size.y + 100)out_window = true;
	}
	int get_ultraSkill_num()
	{
		return num_skill_ultra;
	}
	void set_ultraSkill_num(int n)
	{
		num_skill_ultra = n > 3 ? 3 : n;
	}
protected:
	int id=1;//���id
	Vector2 speed_vector = { 0.0,0.0 };//�ٶ�
	POINT img_size = { 0,0 };//���ͼƬ��С
	float gravity = 1e-3;//��������
	float run_speed=0.1;//�ƶ��ٶ�
	float jump_speed = 0.65;//��Ծ��ʼ�ٶ�
	bool is_collision = false;//�Ƿ���ײ��ƽ̨
	bool out_window = false;
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
	Animation animation_player_normal_attack_left;
	Animation animation_player_normal_attack_right;
	bool facing_right = true;//�Ƿ�����
	//������־
	bool left_key_down=false;
	bool right_key_down = false;
	bool up_key_down = false;
	bool attack_key_down = false;
	bool ex_key_down = false;
	playerCharacter player_character;//�������
	std::vector<DamageObject*> damage_objects;//��ҵķ���������˺��������б�
	float radius_collision = 30;//���ӵ���ײ���뾶

	int blood=100;
	int energy=0;
	std::function<void()> call_back;//�����������
	std::vector<Particle*> list_particle_effects;//�����б�

	int num_skill_ultra = 0;
	bool can_generate_run_effect = true;
	Timer timer_run_effect;//�ܶ����Ӳ�����ʱ��
	Timer timer_interval_attack;//��ͨ���������ʱ��
	bool can_attack = true;//�ܽ��й�����־
};
