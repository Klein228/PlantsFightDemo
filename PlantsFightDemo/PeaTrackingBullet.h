#pragma once
#include"PeaBullet.h"
#include"Player.h"
class PeaTrackingBullet:public PeaBullet
{
public:
	PeaTrackingBullet(int x, int y, bool facing_right,Player* enemy) :PeaBullet(x, y, facing_right) 
	{
		damage += damage;
		energy += energy;
		enemy_player = enemy;
		disappear_timer.set_callback([&] {
			is_out_window = true;
			});
		disappear_timer.set_one_shot(false);
		disappear_timer.set_wait_time(3000);
	};
	~PeaTrackingBullet() {};
	void on_updata(int delta)
	{
		updata_is_out_window();
		disappear_timer.on_updata(delta);
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
			//更新子弹位置
			v = enemy_player->get_pos_center() - get_center_pos();
			v = v.normalize();
			pos_bullet.x += tracking_speed * delta * v.x;
			pos_bullet.y += tracking_speed * delta * v.y;
		}
	}
private:
	Player* enemy_player;
	Vector2 v = { 0,0 };//单位方向向量
	Timer disappear_timer;//子弹存在时间计时
	float tracking_speed = 0.5;//追踪弹速度
};
