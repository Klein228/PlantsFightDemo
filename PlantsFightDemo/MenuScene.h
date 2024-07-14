#pragma once
#include "Scene.h"
#include"SceneManager.h"
#include"Atlas.h"
#include"Animation.h"
#include"Camera.h"

extern SceneManager scene_manager;
extern Atlas game_character_atlas_1_run_right;
class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;
	void on_enter()
	{
		animation_game_character_1_run_right.set_atlas(&game_character_atlas_1_run_right);
		animation_game_character_1_run_right.set_loop(true);
		animation_game_character_1_run_right.set_interval(75);
	}
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			on_exit();
		}
	}
	void on_updata(int delta)
	{
		camera.on_updata(delta);

		animation_game_character_1_run_right.on_updata(delta);
	}
	void on_draw() 
	{
		animation_game_character_1_run_right.on_draw(100-camera.get_position().x, 100-camera.get_position().y);
	}
	void on_exit() 
	{
		std::cout << "ÍË³öÖ÷²Ëµ¥" << std::endl;

	}
private:
	Animation animation_game_character_1_run_right;
	Camera camera;
};

