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
	virtual void set_radius_collision(float f)//���ýӴ��뾶
	{
		radius_collision = f;
	}
	virtual float get_radius_collission()//��ȡ�ӵ��Ӵ��뾶
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
	Animation animation_bullet; //�ӵ�������״̬ͼ
	Animation animation_bullet_explode;//�ӵ��Ӵ����˺�ը����
	POINT img_size = { 0,0 };//�ӵ�ͼƬ��С
	POINT img_explode_size{0,0};//�ӵ���ը�����Ѷ�����С
	Vector2 pos_bullet = { 0,0 };//�ӵ���ǰ��Ⱦλ��
	//Vector2 pos_center_bullet = { 0,0 }; //�ӵ�������λ��
	float radius_collision = 10.0;//�ӵ��ĽӴ��뾶
	Vector2 speed = { 0,0 };//�ӵ��ڸ������ϵ��ٶ�
	int damage = 10;//�ӵ��˺�
	int energy = 10;//�ӵ����лظ�����ֵ
	bool culculated = false;//�ӵ����к��Ƿ������������
	bool is_collision = false; //�ӵ��Ƿ�����ҷ�����ײ
	bool is_exploded_over = false; //�ӵ���ը�����Ƿ����
	bool is_out_window = false;//�ӵ��Ƿ���봰����


};
