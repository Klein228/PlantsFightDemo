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
		//子弹伤害和回蓝量设置
		damage = 5;
		energy = 20;
		//定义子弹初始位置为玩家当前位置
		pos_bullet.x = x;
		pos_bullet.y = y;
		//设置子弹大小
		img_explode_size = { atlas_sunflower_bullet_explode.get_img_at(0)->getwidth(),atlas_sunflower_bullet_explode.get_img_at(0)->getwidth() };
		img_size = { atlas_sunflower_bullet.get_img_at(0)->getwidth(),atlas_sunflower_bullet.get_img_at(0)->getheight() };
		//初始化接触半径
		radius_collision = img_size.x / 3;
		//设置子弹动画初始值
		animation_bullet.set_atlas(&atlas_sunflower_bullet);
		animation_bullet.set_loop(true);
		animation_bullet.set_interval(100);
		animation_bullet_explode.set_atlas(&atlas_sunflower_bullet_explode);
		animation_bullet_explode.set_loop(false);
		animation_bullet_explode.set_interval(100);
		//设置太阳花子弹爆炸效果结束后的回调
		animation_bullet_explode.set_callback([&]() {
			is_exploded_over = true;
			});

		//判断玩家方向确定生成子弹的方向
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
		if (is_exploded_over) //子弹爆炸动画结束
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
	float gravity_sunbullet = 8e-4;//太阳花普通子弹所受重力方向速度变化大小
	float speed_x = 0.4;//太阳花普通子弹的初始x速度
	float speed_y = -0.4;//太阳花普通子弹的初始y速度
};

