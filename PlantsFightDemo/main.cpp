#include"MenuScene.h"
#include"Scene.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"SelectScene.h"
#include"utils.h"
#include"Atlas.h"
#include"Camera.h"

//主菜单图片动画资源加载
IMAGE memu_buckground_img;

//游戏场景资源加载
IMAGE game_background_img;
Atlas game_character_atlas_1_idle;
Atlas game_character_atlas_1_run_right;
Atlas game_character_atlas_1_junp;
Atlas game_character_atlas_1_dead;

//角色选择场景资源加载

Scene* game_scene = nullptr;
Scene* menu_scene = nullptr;
Scene* select_scene = nullptr;
SceneManager scene_manager;
void flip_atlas(Atlas& src, Atlas& dst)
{
	dst.clear_img();
	for (size_t i = 0; i < src.get_size(); i++)
	{
		IMAGE flipped_image;
		flip_image(src.get_img_at(i), &flipped_image);
		dst.add_img(flipped_image);
	}
}
void load_game_resources()
{
	game_character_atlas_1_run_right.load_from_file(_T("resources/Run_%d.png"), 13, 120, 135);
}
int main()
{
	ExMessage msg;
	const int FPS = 60;

	load_game_resources();

	game_scene = new GameScene();
	menu_scene = new MenuScene();
	select_scene = new SelectScene();


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

		static DWORD last_updata_time = GetTickCount();
		DWORD current_updata_time = GetTickCount();
		DWORD delta_time = current_updata_time - last_updata_time;
		scene_manager.on_updata(delta_time);
		last_updata_time = GetTickCount();

		cleardevice();
		scene_manager.on_draw();
		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_begin_time;
		if (frame_delta_time < 1000 / FPS)
		{
			Sleep(1000 / FPS - frame_delta_time);
		}
	}
	delete menu_scene;
	delete game_scene;
	delete select_scene;
	EndBatchDraw();
}