#include"MenuScene.h"
#include"Scene.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"SelectScene.h"
#include"utils.h"
#include"Atlas.h"
#include"Camera.h"
#include"Platform.h"
#include"Player.h"
#include"bullet.h"
#include<vector>
#include<Windows.h>
#include<mciapi.h>
//#include<f>
#pragma comment(lib,"Winmm.lib")

bool is_debug = false;//debug模式
bool is_exit = false;//退出游戏
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
IMAGE img_1P_desc;
IMAGE img_2P_desc;
//玩家角色资源
Atlas atlas_sunflower_run_right;
Atlas atlas_sunflower_idle_right;
Atlas atlas_sunflower_die_right;
Atlas atlas_sunflower_attack_right; 
Atlas atlas_sunflower_run_left;
Atlas atlas_sunflower_idle_left;
Atlas atlas_sunflower_die_left;
Atlas atlas_sunflower_attack_left;

Atlas atlas_peashooter_run_right;
Atlas atlas_peashooter_idle_right;
Atlas atlas_peashooter_die_right;
Atlas atlas_peashooter_attack_right;
Atlas atlas_peashooter_run_left;
Atlas atlas_peashooter_idle_left;
Atlas atlas_peashooter_die_left;
Atlas atlas_peashooter_attack_left;
//游戏场景资源加载
IMAGE img_hills;
IMAGE img_sky;
IMAGE img_platform_large;
IMAGE img_platform_small;
IMAGE img_cursor_1P;
IMAGE img_cursor_2P;
IMAGE img_sunflower_head;
IMAGE img_peashooter_head;
IMAGE img_1P_winner;
IMAGE img_2P_winner;
IMAGE img_winner_bar;
Atlas atlas_sun_text;
//子弹
Atlas atlas_sunflower_bullet;
Atlas atlas_sunflower_bullet_ex;
Atlas atlas_sunflower_bullet_explode;
Atlas atlas_sunflower_bullet_ex_explode;

Atlas atlas_peashooter_bullet;
Atlas atlas_peashooter_bullet_explode;
//粒子系统
Atlas atlas_run_effect;
Atlas atlas_jump_effect;
//道具资源
IMAGE img_prop;

Scene* game_scene = nullptr;
Scene* menu_scene = nullptr;
Scene* select_scene = nullptr;
SceneManager scene_manager;

Camera main_camera;

Player* player1=nullptr;
Player* player2=nullptr;
std::vector<Platform> list_platform;
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
	loadimage(&img_1P_desc, L"resources/1P_desc.png");
	loadimage(&img_2P_desc, L"resources/2P_desc.png");
	loadimage(&img_sky, L"resources/sky.png");
	loadimage(&img_hills, L"resources/hills.png");
	loadimage(&img_platform_large, L"resources/platform_large.png");
	loadimage(&img_platform_small, L"resources/platform_small.png");

	loadimage(&img_cursor_1P, L"resources/1P_cursor.png");
	loadimage(&img_cursor_2P, L"resources/2P_cursor.png");

	loadimage(&img_sunflower_head, L"resources/avatar_sunflower.png");
	loadimage(&img_peashooter_head, L"resources/avatar_peashooter.png");
	loadimage(&img_1P_winner, L"resources/1P_winner.png");
	loadimage(&img_2P_winner, L"resources/2P_winner.png");
	loadimage(&img_winner_bar, L"resources/winnner_bar.png");

	loadimage(&img_prop, L"resources/Chest.png",80,60);

	atlas_sunflower_idle_right.load_from_file(L"resources/sunflower_idle_%d.png", 8);
	atlas_sunflower_die_right.load_from_file(L"resources/sunflower_die_%d.png", 2);
	atlas_sunflower_run_right.load_from_file(L"resources/sunflower_run_%d.png", 5);
	atlas_sunflower_attack_right.load_from_file(L"resources/sunflower_attack_ex_%d.png", 9);
	flip_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	flip_atlas(atlas_sunflower_attack_right, atlas_sunflower_attack_left);
	flip_atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);
	flip_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);

	atlas_peashooter_idle_right.load_from_file(L"resources/peashooter_idle_%d.png", 9);
	atlas_peashooter_die_right.load_from_file(L"resources/peashooter_die_%d.png", 4);
	atlas_peashooter_run_right.load_from_file(L"resources/peashooter_run_%d.png", 5);
	atlas_peashooter_attack_right.load_from_file(L"resources/peashooter_attack_ex_%d.png", 3);
	flip_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	flip_atlas(atlas_peashooter_attack_right, atlas_peashooter_attack_left);
	flip_atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);
	flip_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);

	atlas_sunflower_bullet.load_from_file(L"resources/sun_%d.png", 5);
	atlas_sunflower_bullet_ex.load_from_file(L"resources/sun_ex_%d.png", 5);
	atlas_sunflower_bullet_explode.load_from_file(L"resources/sun_explode_%d.png", 5);
	atlas_sunflower_bullet_ex_explode.load_from_file(L"resources/sun_ex_explode_%d.png", 5);

	atlas_peashooter_bullet.load_from_file(L"resources/pea%d.png",1);
	atlas_peashooter_bullet_explode.load_from_file(L"resources/pea_break_%d.png", 3);

	atlas_sun_text.load_from_file(L"resources/sun_text_%d.png", 6);

	atlas_run_effect.load_from_file(L"resources/run_effect_%d.png", 4);
	atlas_jump_effect.load_from_file(L"resources/jump_effect_%d.png", 5);
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
	mciSendString(_T("open resources/Jump_03.mp3 alias jump"), NULL, 0, NULL);
	mciSendString(_T("open resources/run.wav alias run"), NULL, 0, NULL);

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
	setbkmode(TRANSPARENT);

	scene_manager.set_current_scene(menu_scene);

	BeginBatchDraw();
	while (!is_exit)
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