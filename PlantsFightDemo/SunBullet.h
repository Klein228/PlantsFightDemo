#pragma once
#include"bullet.h"
#include"Camera.h"
extern Atlas atlas_sunflower_bullet;
extern Atlas atlas_sunflower_bullet_explode;
class SunBullet:public Bullet
{
public:
	SunBullet(int x,int y,bool facing_right):Bullet()
	{
		//�ӵ��˺��ͻ���������
		damage = 5;
		energy = 20;
		//�����ӵ���ʼλ��Ϊ��ҵ�ǰλ��
		pos_bullet.x = x;
		pos_bullet.y = y;
		//�����ӵ���С
		img_explode_size = { atlas_sunflower_bullet_explode.get_img_at(0)->getwidth(),atlas_sunflower_bullet_explode.get_img_at(0)->getwidth() };
		img_size = { atlas_sunflower_bullet.get_img_at(0)->getwidth(),atlas_sunflower_bullet.get_img_at(0)->getheight() };
		//��ʼ���Ӵ��뾶
		radius_collision = img_size.x / 3;
		//�����ӵ�������ʼֵ
		animation_bullet.set_atlas(&atlas_sunflower_bullet);
		animation_bullet.set_loop(true);
		animation_bullet.set_interval(100);
		animation_bullet_explode.set_atlas(&atlas_sunflower_bullet_explode);
		animation_bullet_explode.set_loop(false);
		animation_bullet_explode.set_interval(100);
		//����̫�����ӵ���ըЧ��������Ļص�
		animation_bullet_explode.set_callback([&]() {
			is_exploded_over = true;
			});

		//�ж���ҷ���ȷ�������ӵ��ķ���
		if (facing_right)
		{
			speed.x = speed_x;
		}
		else
		{
			speed.x = -speed_x;
		}
		speed.y = speed_y;
	}
	~SunBullet()
	{}
	void on_updata(int delta)
	{
		updata_is_out_window();
		if (is_exploded_over) //�ӵ���ը��������
		{
			return;
		}
		if (is_collision)
		{
			animation_bullet_explode.on_updata(delta);
		}
		else
		{
			animation_bullet.on_updata(delta);
			speed.y += gravity_sunbullet * delta;
			pos_bullet.x += speed.x * delta;
			pos_bullet.y += speed.y * delta;
		}
		
		
	}
	void on_draw(Camera& camera)
	{
		if (is_debug)
		{
			circle(get_center_pos().x, get_center_pos().y, radius_collision);
		}
		if (is_exploded_over) //�ӵ���ը��������
		{
			return;
		}
		if (is_collision)
		{
			animation_bullet_explode.on_draw(pos_bullet.x + (img_size.x - img_explode_size.x) / 2, pos_bullet.y + (img_size.y - img_explode_size.y) / 2);
		}
		else
		{
			animation_bullet.on_draw(pos_bullet.x, pos_bullet.y);
		}
		
	}

private:
	float gravity_sunbullet = 8e-4;//̫������ͨ�ӵ��������������ٶȱ仯��С
	float speed_x = 0.4;//̫������ͨ�ӵ��ĳ�ʼx�ٶ�
	float speed_y = -0.4;//̫������ͨ�ӵ��ĳ�ʼy�ٶ�
};

