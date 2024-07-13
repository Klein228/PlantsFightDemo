#include"MenuScene.h"
#include"Scene.h"
#include"GameScene.h"
#include"SceneManager.h"
Scene* game_scene = nullptr;
Scene* menu_scene = nullptr;

SceneManager scene_manager;
int main()
{
	ExMessage msg;
	const int FPS = 60;

	
	game_scene = new GameScene();
	menu_scene = new MenuScene();
	

	initgraph(1280, 720);

	scene_manager.set_current_scene(menu_scene);
	BeginBatchDraw();
	while (true)
	{
		DWORD frame_begin_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}

		scene_manager.on_updata();

		cleardevice();
		scene_manager.on_draw();
		menu_scene->on_draw();
		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_begin_time;
		if ( frame_delta_time< 1000 / FPS)
		{
			Sleep(1000 / FPS - frame_delta_time);
		}
	}
	delete menu_scene;
	delete game_scene;
	EndBatchDraw();
}