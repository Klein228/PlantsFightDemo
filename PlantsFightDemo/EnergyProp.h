#pragma once
#include"Prop.h"
extern IMAGE img_energy_prop;
class EnergyProp :public Prop
{
public:
	EnergyProp(int x, int y, Player* ply1, Player* ply2) :Prop(x, y, ply1, ply2)
	{
		this_prop_img = &img_energy_prop;
		size.x = this_prop_img->getwidth();
		size.y = this_prop_img->getheight();
	};
	~EnergyProp() {};
	void player1_touched() override
	{
		p1->set_energy(p1->get_energy() + energy);
	}
	void player2_touched() override
	{
		p2->set_energy(p2->get_energy() + energy);
	}
private:
	int energy = 50;
};