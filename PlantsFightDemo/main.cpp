#include"MenuScene.h"
#include"Scene.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"SelectScene.h"
#include"utils.h"
#include"Atlas.h"
#include"Camera.h"
#include<Windows.h>
#include<mciapi.h>
#pragma comment(lib,"Winmm.lib")

//设置窗口大小
const POINT window_size = {1280,720};
//主菜单场景资源加载
IMAGE img_memu_background;

//角色选择场景资源加载
IMAGE img_select_scene_background;
IMAGE img_start_game_tip;
IMAGE img_start_game_tip_black;
IMAGE img_character_table;
IMAGE img_character_table_flipped;
IMAGE img_1P;
IMAGE img_1P_black;
IMAGE img_2P;
IMAGE img_2P_black;
IMAGE img_1P_selector_btn_right;
IMAGE img_1P_selector_btn_right_down;
IMAGE img_1P_selector_btn_left;
IMAGE img_1P_selector_btn_left_down;
IMAGE img_2P_selector_btn_right;
IMAGE img_2P_selector_btn_right_down;
IMAGE img_2P_selector_btn_left;
IMAGE img_2P_selector_btn_left_down;
IMAGE img_vs;
//游戏场景资源加载



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
	//图片资源
	loadimage(&img_memu_background, L"resources/menu_background.png", window_size.x, window_size.y);
	loadimage(&img_select_scene_background, L"resources/selector_background.png", window_size.x, window_size.y);
	loadimage(&img_start_game_tip, L"resources/selector_tip.png");
	black_image(&img_start_game_tip, &img_start_game_tip_black);
	loadimage(&img_character_table, L"resources/gravestone.png");
	flip_image(&img_character_table, &img_character_table_flipped);
	loadimage(&img_1P, L"resources/1P.png");
	black_image(&img_1P, &img_1P_black);
	loadimage(&img_2P, L"resources/2P.png");
	black_image(&img_2P, &img_2P_black);
	loadimage(&img_1P_selector_btn_right, L"resources/1P_selector_btn_idle.png");
	loadimage(&img_1P_selector_btn_right_down, L"resources/1P_selector_btn_down.png");
	flip_image(&img_1P_selector_btn_right, &img_1P_selector_btn_left);
	flip_image(&img_1P_selector_btn_right_down, &img_1P_selector_btn_left_down);
	loadimage(&img_2P_selector_btn_right, L"resources/2P_selector_btn_idle.png");
	loadimage(&img_2P_selector_btn_right_down, L"resources/2P_selector_btn_down.png");
	flip_image(&img_2P_selector_btn_right, &img_2P_selector_btn_left);
	flip_image(&img_2P_selector_btn_right_down, &img_2P_selector_btn_left_down);
	loadimage(&img_vs, L"resources/VS.png");
	//音乐
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);
	mciSendString(_T("open resources/impact_btn.wav alias btn"), NULL, 0, NULL);
}
int main()
{
	ExMessage msg;
	const int FPS = 60;

	load_game_resources();

	game_scene = new GameScene();
	menu_scene = new MenuScene();
	select_scene = new SelectScene();


	initgraph(window_size.x, window_size.y);

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