#pragma once
#include "Scene.h"
#include"SceneManager.h"
#include"Atlas.h"
#include"Animation.h"
#include"Camera.h"
#include"Timer.h"
extern SceneManager scene_manager;
extern IMAGE img_memu_background;

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;
	void on_enter()
	{
		mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
	}
	void on_input(const ExMessage& msg)
	{
		
		if (msg.message == WM_KEYUP)
		{
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager.switch_to(SceneManager::sceneType::Select);

		}
		
	}
	void on_updata(int delta)
	{

	}
	void on_draw() 
	{
		putimage_alpha(0, 0, &img_memu_background);
	}
	void on_exit() 
	{

	}
private:
	Camera camera;
};

