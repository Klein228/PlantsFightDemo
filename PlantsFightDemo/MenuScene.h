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
		std::cout << "进入主菜单" << std::endl;
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
		std::cout << "主菜单正在运行" << std::endl;
	}
	void on_draw() 
	{
		outtextxy(0, 0, _T("主菜单绘图内容"));
	}
	void on_exit() 
	{
		std::cout << "退出主菜单" << std::endl;
	}
};

