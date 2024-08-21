#pragma once
#include"Prop.h"
#include<vector>
extern IMAGE img_prop;
class PropManager
{
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
		//�������λ��
		int rand_x = rand() % (getwidth()-img_prop.getwidth());
		int rand_y = 0-img_prop.getheight();
		Prop* new_prop = new Prop(rand_x,rand_y,player1,player2);
		prop_list.push_back(new_prop);
	};//��������µ���
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
	std::vector<Prop*> prop_list;//������е��߶���
	Player* player1;
	Player* player2;
};
