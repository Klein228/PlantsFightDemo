#pragma once
#include"Prop.h"
#include"BloodProp.h"
#include"EnergyProp.h"
#include"UltraSkillProp.h"
#include<vector>
extern IMAGE img_prop;
class PropManager
{
public:
	enum class propType {
		blood,
		energy,
		ultra_skill,
		total_num
	};
public:
	PropManager(Player* p1, Player* p2)
	{
		player1 = p1;
		player2 = p2;
	};
	~PropManager() 
	{
		for (size_t i = 0; i < prop_list.size(); i++)
		{
			delete prop_list[i];
		}
	};
	void generate_prop() {
		//随机生成位置
		int rand_x = rand() % (getwidth()-img_prop.getwidth());
		int rand_y = 0-img_prop.getheight();
		Prop* new_prop;
		switch ((PropManager::propType)(rand_x%(int)(propType::total_num)))
		{
		case PropManager::propType::blood:
			new_prop = new BloodProp(rand_x, rand_y, player1, player2);
			break;
		case PropManager::propType::energy:
			new_prop = new EnergyProp(rand_x, rand_y, player1, player2);
			break;
		case PropManager::propType::ultra_skill:
			new_prop = new UltraSkillProp(rand_x, rand_y, player1, player2);
			break;
		case PropManager::propType::total_num:
			break;
		default:
			break;
		}
		prop_list.push_back(new_prop);
	};//生成随机新道具
	void on_updata(int delta)
	{
		for (size_t i = 0; i < prop_list.size(); i++)
		{
			prop_list[i]->on_updata(delta);
		}
		updata_list();
	};
	void updata_list()
	{
		int i = 0;
		int j = prop_list.size() - 1;
		while (i < j)
		{
			if (!prop_list[i]->get_live())
			{
				auto temp = prop_list[i];
				prop_list[i] = prop_list[j];
				delete temp;
				prop_list.pop_back();
				j--;
			}
			else
			{
				i++;
			}
		}
	}
	void on_draw(Camera& camera)
	{
		for (size_t i = 0; i < prop_list.size(); i++)
		{
			if(prop_list[i]->get_live())prop_list[i]->on_draw(camera);
		}
	};
private:
	std::vector<Prop*> prop_list;//存放所有道具对象
	Player* player1;
	Player* player2;
};
