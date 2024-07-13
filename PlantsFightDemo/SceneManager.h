#pragma once
#include"Scene.h"
extern Scene* game_scene;
extern Scene* menu_scene;
class SceneManager
{
public:
	enum class sceneType
	{
		Menu,
		Game
	};
public:
	SceneManager() = default;
	~SceneManager() = default;
	void set_current_scene(Scene* scene)
	{
		current_scene = scene;
		current_scene->on_enter();
	}
	void switch_to(sceneType type)
	{
		current_scene->on_exit();
		switch (type)
		{
		case SceneManager::sceneType::Menu:
			current_scene = menu_scene;
			break;
		case SceneManager::sceneType::Game:
			current_scene = game_scene;
			break;
		default:
			break;
		}
		current_scene->on_enter();
	}
	void on_input(const ExMessage& msg)
	{
		current_scene->on_input(msg);
	}
	void on_updata()
	{
		current_scene->on_updata();
	}
	void on_draw()
	{
		current_scene->on_draw();
	}
private:
	Scene* current_scene = nullptr;
};