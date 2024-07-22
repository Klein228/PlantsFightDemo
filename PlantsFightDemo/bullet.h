#pragma once
#include"graphics.h"
#include"Vector2.h"
#include"Animation.h"
class Bullet
{

public:
	Bullet() {};
	~Bullet() {};
	virtual void on_updata(int delta)
	{}
	virtual void on_draw(Camera& camera)
	{}
	virtual void set_position(Vector2 p)
	{
		pos_bullet = p;
	}
	virtual Vector2 get_position()
	{
		return pos_bullet;
	}
	virtual void set_radius_collision(float f)//设置接触半径
	{
		radius_collision = f;
	}
	virtual float get_radius_collission()//获取子弹接触半径
	{
		return radius_collision;
	}
	void set_is_collision(bool b)
	{
		is_collision = b;
	}
	bool get_is_collision()
	{
		return is_collision;
	}
	void set_is_exploded_over(bool b)
	{
		is_exploded_over = b;
	}
	bool get_is_exploded_over()
	{
		return is_exploded_over;
	}
	void set_bullet_damage(int d)
	{
		damage = d;
	}
	int get_bullet_damage()
	{
		return damage;
	}
	Vector2 get_center_pos()
	{
		return {pos_bullet.x+img_size.x/2,pos_bullet.y + img_size.y / 2 };
	}
	void updata_is_out_window()
	{
		if (pos_bullet.x > getwidth() || pos_bullet.y > getheight())
			is_out_window = true;
	}
	bool get_is_out_window()
	{
		return is_out_window;
	}
	int get_energy()
	{
		return energy;
	}
	bool get_is_culculated()
	{
		return culculated;
	}
	void set_is_culculated(bool b)
	{
		culculated = b;
	}
protected:
	Animation animation_bullet; //子弹的正常状态图
	Animation animation_bullet_explode;//子弹接触敌人后爆炸动画
	POINT img_size = { 0,0 };//子弹图片大小
	POINT img_explode_size{0,0};//子弹爆炸或破裂动画大小
	Vector2 pos_bullet = { 0,0 };//子弹当前渲染位置
	//Vector2 pos_center_bullet = { 0,0 }; //子弹的中心位置
	float radius_collision = 10.0;//子弹的接触半径
	Vector2 speed = { 0,0 };//子弹在各方向上的速度
	int damage = 10;//子弹伤害
	int energy = 10;//子弹命中回复能量值
	bool culculated = false;//子弹命中后是否计算能量增加
	bool is_collision = false; //子弹是否与玩家发生碰撞
	bool is_exploded_over = false; //子弹爆炸动画是否结束
	bool is_out_window = false;//子弹是否掉入窗口外


};
