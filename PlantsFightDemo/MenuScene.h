#pragma once
#include "Scene.h"
#include"SceneManager.h"

extern SceneManager scene_manager;
class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;
	void on_enter()
	{
		std::cout << "�������˵�" << std::endl;
	}
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.switch_to(SceneManager::sceneType::Game);
		}
	}
	void on_updata()
	{
		std::cout << "���˵���������" << std::endl;
	}
	void on_draw() 
	{
		outtextxy(0, 0, _T("���˵���ͼ����"));
	}
	void on_exit() 
	{
		std::cout << "�˳����˵�" << std::endl;
	}
};

