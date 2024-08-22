#pragma once
#include"Prop.h"
extern IMAGE img_prop;
class UltraSkillProp:public Prop
{
public:
	UltraSkillProp(int x, int y, Player* ply1, Player* ply2) :Prop(x, y, ply1, ply2)
	{
		this->this_prop_img = &img_prop;
		size.x = this_prop_img->getwidth();
		size.y = this_prop_img->getheight();
	};
	~UltraSkillProp() {};
	void player1_touched() override
	{
		p1->set_ultraSkill_num(p1->get_ultraSkill_num()+1);
	}
	void player2_touched() override
	{
		p2->set_ultraSkill_num(p2->get_ultraSkill_num() + 1);
	}
private:

};
