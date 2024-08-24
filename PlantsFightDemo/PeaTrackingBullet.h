#pragma once
#include"PeaBullet.h"
#include"Player.h"
#include"Vector3D.h"
#define PI 3.1415926
class PeaTrackingBullet:public PeaBullet
{
public:
	PeaTrackingBullet(int x, int y, bool facing_right,Player* enemy) :PeaBullet(x, y, facing_right) 
	{
		damage += damage;
		energy += energy;
		v_now.x = facing_right ? 1 : -1;
		enemy_player = enemy;
		disappear_timer.set_callback([&] {
			is_out_window = true;
			});
		disappear_timer.set_one_shot(false);
		disappear_timer.set_wait_time(3000);
		timer_angle_change.set_one_shot(false);
		timer_angle_change.set_wait_time(100);
		timer_angle_change.set_callback([&] {
			can_change_angle = true;
			});
	};
	~PeaTrackingBullet() {};
	void on_updata(int delta)
	{
		updata_is_out_window();
		disappear_timer.on_updata(delta);
		timer_angle_change.on_updata(delta);
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
			Vector3D vector3d = Vector3D(v_now.x, v_now.y, 0).Cross(Vector3D(v.x, v.y, 0));
			auto theta = AngleBetweenVectors(v_now, v);
			if (theta > (angle / 180 * PI) && can_change_angle)
			{
				if (vector3d.z > 0)
				{
					v_now = RotateVectorByMatrix(v_now, -angle);
				}
				else
				{
					v_now = RotateVectorByMatrix(v_now, angle);
				}
				can_change_angle = false;
			}
			pos_bullet.x += tracking_speed * delta * v_now.x;
			pos_bullet.y += tracking_speed * delta * v_now.y;
		}
	}
private:
	Player* enemy_player;
	Vector2 v_now = { 0,0 };//当前速度方向单位向量
	Vector2 v = { 0,0 };//目标方向单位方向向量
	Timer disappear_timer;//子弹存在时间计时
	float tracking_speed = 0.5;//追踪弹速度
	float angle = 5;//追踪弹最大变化角度(0-90)
	Timer timer_angle_change;//子弹角度变化时间计时器
	bool can_change_angle=true;//子弹角度变化标志
};
