#pragma once
#include"bullet.h"
extern bool is_debug;
extern Atlas atlas_peashooter_bullet;
extern Atlas atlas_peashooter_bullet_explode;
class PeaBullet:public Bullet
{
public:
	PeaBullet(int x,int y,bool facing_right):Bullet()
	{
		bullet_type = peabullet;
		//子弹伤害和回蓝量设置
		damage = 1;
		energy = 5;
		//子弹图片设置
		img_explode_size = { atlas_peashooter_bullet_explode.get_img_at(0)->getwidth(),atlas_peashooter_bullet_explode.get_img_at(0)->getheight() };
		img_size = { atlas_peashooter_bullet.get_img_at(0)->getwidth(),atlas_peashooter_bullet.get_img_at(0)->getheight() };
		//子弹渲染位置初始化
		pos_bullet.x = x;
		pos_bullet.y = y;
		//子弹速度
		if (facing_right)speed.x = 1;
		else speed.x = -1;
		//动画初始化
		animation_bullet.set_atlas(&atlas_peashooter_bullet);
		animation_bullet.set_interval(20);
		animation_bullet.set_loop(true);
		animation_bullet_explode.set_atlas(&atlas_peashooter_bullet_explode);
		animation_bullet_explode.set_interval(100);
		animation_bullet_explode.set_loop(false);
		animation_bullet_explode.set_callback([&]() {
			is_exploded_over = true;
			});
	}
	~PeaBullet(){}
	virtual void on_updata(int delta)
	{
		updata_is_out_window();
		if (is_exploded_over) //子弹爆炸动画结束
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
			pos_bullet.x += speed.x * delta;
		}


	}
	void on_draw(Camera& camera)
	{
		if (is_debug)
		{
			circle(get_center_pos().x, get_center_pos().y, radius_collision);
		}
		if (is_exploded_over) //子弹爆炸动画结束
		{
			return;
		}
		if (is_collision)
		{
			animation_bullet_explode.on_draw(pos_bullet.x+(img_size.x-img_explode_size.x)/2, pos_bullet.y+ (img_size.y - img_explode_size.y) / 2);
		}
		else
		{
			animation_bullet.on_draw(pos_bullet.x, pos_bullet.y);
		}

	}
private:

};
