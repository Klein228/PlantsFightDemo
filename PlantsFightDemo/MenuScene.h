#pragma once
#include "Scene.h"
#include"SceneManager.h"
#include"Atlas.h"
#include"Animation.h"
#include"Camera.h"
#include"Timer.h"
extern SceneManager scene_manager;
extern IMAGE memu_background_img;
extern IMAGE menu_start_game_img_default;
extern IMAGE menu_start_game_img_hover;

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;
	void on_enter()
	{
		start_btn_position.x = (getwidth() - menu_start_game_img_default.getwidth()) / 2;
		start_btn_position.y = getheight()*1/2;
	}
	void on_input(const ExMessage& msg)
	{
		//判断鼠标位更新开始按钮图片
		if (msg.message == WM_MOUSEMOVE)
		{
			if (msg.x >= start_btn_position.x && msg.x <= start_btn_position.x + menu_start_game_img_default.getwidth() &&
				msg.y >= start_btn_position.y && msg.y <= start_btn_position.y + menu_start_game_img_default.getheight())
				mouse_hover_on_btn = true;
			else
			{
				mouse_hover_on_btn = false;
			}
		}
		//判断是否在开始按钮位置按下鼠标左键
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= start_btn_position.x && msg.x <= start_btn_position.x + menu_start_game_img_default.getwidth() &&
				msg.y >= start_btn_position.y && msg.y <= start_btn_position.y + menu_start_game_img_default.getheight())
				scene_manager.switch_to(SceneManager::sceneType::Select);
		}
	}
	void on_updata(int delta)
	{

	}
	void on_draw() 
	{
		putimage_alpha(0, 0, &memu_background_img);
		putimage_alpha(start_btn_position.x, start_btn_position.y, (mouse_hover_on_btn) ? &menu_start_game_img_hover : &menu_start_game_img_default);
	}
	void on_exit() 
	{

	}
private:
	Camera camera;
	bool mouse_hover_on_btn = false;
	POINT start_btn_position = { 0,0 };
};

