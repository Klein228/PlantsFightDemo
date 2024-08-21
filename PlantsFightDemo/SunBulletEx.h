#pragma once
#include"SunBullet.h"
extern bool is_debug;
extern Atlas atlas_sunflower_bullet_ex;
extern Atlas atlas_sunflower_bullet_ex_explode;
class SunBulletEx:public Bullet
{
public:
	SunBulletEx(int x,int y):Bullet()
	{
		bullet_type = sunbulletex;
		//子弹伤害和回蓝量设置
		damage = 20;
		energy = 50;
		//设置子弹大小
		img_explode_size = { atlas_sunflower_bullet_ex_explode.get_img_at(0)->getwidth(),atlas_sunflower_bullet_ex_explode.get_img_at(0)->getwidth() };
		img_size = { atlas_sunflower_bullet_ex.get_img_at(0)->getwidth(),atlas_sunflower_bullet_ex.get_img_at(0)->getheight() };
		//初始化子弹的接触半径
		radius_collision = img_size.x / 3;
		//定义子弹初始位置为敌方玩家中心位置上方500像素处
		pos_bullet.x = x-img_size.x/2;
		pos_bullet.y = y-img_size.y/2-500;
		//设置子弹动画初始值
		animation_bullet.set_atlas(&atlas_sunflower_bullet_ex);
		animation_bullet.set_loop(true);
		animation_bullet.set_interval(100);
		animation_bullet_explode.set_atlas(&atlas_sunflower_bullet_ex_explode);
		animation_bullet_explode.set_loop(false);
		animation_bullet_explode.set_interval(100);
		//设置太阳花子弹爆炸效果结束后的回调
		animation_bullet_explode.set_callback([&]() {
			is_exploded_over = true;
			});

		//设置子弹下落速度
		speed.y = speed_y;
	}
	~SunBulletEx() {}
	void on_updata(int delta)
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
			pos_bullet.y += speed.y * delta;
		}
	}
	void on_draw(Camera &camera)
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
	Vector2 bullet_speed = { 0,0 };
	float speed_x = 0;
	float speed_y = 0.4;
};
