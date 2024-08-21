#pragma once
#include<graphics.h>
#include"utils.h"
#include"Camera.h"
#include"Vector2.h"
#include"Player.h"
extern IMAGE img_prop;
extern bool is_debug;
class Prop
{
public:
	Prop(int x, int y,Player *ply1,Player *ply2)
	{
		size.x = img_prop.getwidth();
		size.y = img_prop.getheight();
		pos.x = x, pos.y = y;
		p1 = ply1;
		p2 = ply2;
	};
	~Prop() {};
	void on_updata(int delta)
	{
		if (pos.y > getheight())out_window = true;
		pos.y += delta * speed.y;
		get_by_player();
	};
	void on_draw(Camera& camera)
	{
		putimage_alpha(pos.x, pos.y, &img_prop, &camera);
		if (is_debug)
		{
			rectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
		}
	};
	void get_by_player()
	{
		Vector2 p_position = p1->get_pos_center();
		if (p_position.x >= pos.x && p_position.x <= pos.x + size.x &&
			p_position.y >= pos.y && p_position.y <= pos.y + size.y &&!used)
		{
			used = true;
			p1->set_blood(p1->get_blood() + 20);
		}
		p_position = p2->get_pos_center();
		if (p_position.x >= pos.x && p_position.x <= pos.x + size.x &&
			p_position.y >= pos.y && p_position.y <= pos.y + size.y && !used)
		{
			used = true;
			p2->set_blood(p2->get_blood() + 20);
		}
	};//触碰到玩家后效果函数
	bool get_live()
	{
		if (used || out_window)return false;
		else return true;
	}
private:
	Vector2 pos = { 0,0 };//渲染位置
	bool used = false;//道具是否已被使用
	bool out_window = false;//道具是否掉出窗口
	POINT size={0,0};
	Player* p1;
	Player* p2;
	Vector2 speed = { 0,5e-2};
};