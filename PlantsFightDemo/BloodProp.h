#pragma once
#include"Prop.h"
extern IMAGE img_blood_prop;
class BloodProp :public Prop
{
public:
	BloodProp(int x, int y, Player* ply1, Player* ply2) :Prop(x, y, ply1, ply2) 
	{
		this_prop_img = &img_blood_prop;
		size.x = this_prop_img->getwidth();
		size.y = this_prop_img->getheight();
	};
	~BloodProp() {};
	void player1_touched() override 
	{
		p1->set_blood(p1->get_blood() + blood);
	}
	void player2_touched() override
	{
		p2->set_blood(p2->get_blood() + blood);
	}
private:
	int blood = 20;
};
