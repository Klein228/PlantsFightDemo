#pragma once
#include"Player.h"
#include"Camera.h"
#include"Vector2.h"
class DamageObject
{
public:
	DamageObject() {};
	~DamageObject() {};

	virtual bool player_collision(Vector2 p, float r) {
		return false;
	}
	virtual void on_updata(int delta){}
	virtual void on_draw(Camera& camera){}
	virtual void play_collision_music(){}
	virtual bool object_over()
	{
		return false;
	}
	virtual void set_is_collision(bool b)
	{
		is_collision = b;
	}
	virtual bool get_is_collision()
	{
		return is_collision;
	}
	virtual void set_damage(int d)
	{
		damage = d;
	}
	virtual int get_damage()
	{
		return damage;
	}
	virtual int get_energy()
	{
		return energy;
	}
	virtual bool get_is_culculated()
	{
		return culculated;
	}
	virtual void set_is_culculated(bool b)
	{
		culculated = b;
	}
	enum bulletType
	{
		peabullet,
		sunbullet,
		sunbulletex,
		nobullet
	}bullet_type;
protected:
	bool is_collision = false; //是否与玩家发生碰撞
	int damage = 5;
	int energy = 2;
	bool culculated = false;

};
