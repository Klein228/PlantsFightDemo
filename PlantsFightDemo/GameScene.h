#pragma once
#include "Scene.h"
#include"SceneManager.h"
#include"SelectScene.h"
#include"Platform.h"
#include"Player.h"
#include"PropManager.h"
extern SceneManager scene_manager;
extern IMAGE img_hills;
extern IMAGE img_sky;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;
extern IMAGE img_cursor_1P;
extern IMAGE img_cursor_2P;
extern IMAGE img_sunflower_head;
extern IMAGE img_peashooter_head;
extern IMAGE img_ninja_head;
extern IMAGE img_1P_winner;
extern IMAGE img_2P_winner;
extern IMAGE img_winner_bar;
extern IMAGE img_coins;
extern Camera main_camera;
extern std::vector<Platform> list_platform;
extern bool is_debug;
extern Player* player1;
extern Player* player2;

class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;
	enum class Winner
	{
		p1,
		p2,
		no_winner
	};
	void on_enter() {
		mciSendString(L"play bgm_game repeat from 0", NULL, 0, NULL);
		pos_hills.x = (getwidth() - img_hills.getwidth()) / 2;
		pos_hills.y = (getheight() - img_hills.getheight()) / 2;
		pos_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_sky.y = (getheight() - img_sky.getheight()) / 2;

		list_platform.resize(4);
		Platform& large_platform = list_platform[0];
		large_platform.img = &img_platform_large;
		large_platform.pos_render = { 122,455 };
		large_platform.shape.x_begin = large_platform.pos_render.x + 30;
		large_platform.shape.x_end = large_platform.pos_render.x + img_platform_large.getwidth() - 30;
		large_platform.shape.y = large_platform.pos_render.y + 60;

		Platform& small_platform_1 = list_platform[1];
		small_platform_1.img = &img_platform_small;
		small_platform_1.pos_render = { 175,360 };
		small_platform_1.shape.x_begin = small_platform_1.pos_render.x + 40;
		small_platform_1.shape.x_end = small_platform_1.pos_render.x + img_platform_small.getwidth() - 40;
		small_platform_1.shape.y = small_platform_1.pos_render.y + img_platform_small.getheight() / 2;

		Platform& small_platform_2 = list_platform[2];
		small_platform_2.img = &img_platform_small;
		small_platform_2.pos_render = { 855,360 };
		small_platform_2.shape.x_begin = small_platform_2.pos_render.x + 40;
		small_platform_2.shape.x_end = small_platform_2.pos_render.x + img_platform_small.getwidth() - 40;
		small_platform_2.shape.y = small_platform_2.pos_render.y + img_platform_small.getheight() / 2;

		Platform& small_platform_3 = list_platform[3];
		small_platform_3.img = &img_platform_small;
		small_platform_3.pos_render = { 515,255 };
		small_platform_3.shape.x_begin = small_platform_3.pos_render.x + 40;
		small_platform_3.shape.x_end = small_platform_3.pos_render.x + img_platform_small.getwidth() - 40;
		small_platform_3.shape.y = small_platform_3.pos_render.y + img_platform_small.getheight() / 2;
		//光标尺寸初始化
		size_cursor = { img_cursor_1P.getwidth(),img_cursor_1P.getheight() };
		//光标显示计时初始化
		timer_cursor_view.set_one_shot(true);
		timer_cursor_view.set_wait_time(2000);
		timer_cursor_view.set_callback([&]() {
			cursor_timeout = true;
			});

		//角色类型 传递到本场景
		p1_character = player1->get_player_type();
		p2_character = player2->get_player_type();
		//初始化玩家回调函数
		player1->set_call_back([&]() {
			game_over = true;
			winner_id = 2;
			});
		player2->set_call_back([&]() {
			game_over = true;
			winner_id = 1;
			});
		//道具管理器初始化
		prop_manager = new PropManager(player1, player2);
		//道具生成计时器初始化
		timer_prop_generate.set_one_shot(false);
		timer_prop_generate.set_callback([&] {
			prop_manager->generate_prop();
			});
		timer_prop_generate.set_wait_time(5000);
	}
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case 'Q':
				is_debug = !is_debug;
				break;
			default:
				break;
			}
		}
		if(game_over)
		{ 
			if (msg.message == WM_KEYDOWN)
			{
				switch (msg.vkcode)
				{
				case VK_ESCAPE:
					scene_manager.switch_to(SceneManager::sceneType::Select);
					break;
				default:
					break;
				}
			}
		}
		else
		{
			player1->on_input(msg);
			player2->on_input(msg);
		}

	}
	void on_updata(int delta)
	{
		if (game_over)
		{
			percent_over_tie += speed_over_tie;
			if (percent_over_tie >= 1)percent_over_tie = 1;
		}
		else
		{
			main_camera.on_updata(delta);
			timer_cursor_view.on_updata(delta);
			timer_prop_generate.on_updata(delta);
			player1->damage_objects_collision(player2->get_damage_objects());
			player2->damage_objects_collision(player1->get_damage_objects());
			player1->set_enemy_player_center_pos(player2->get_pos_center());
			player2->set_enemy_player_center_pos(player1->get_pos_center());
			player1->on_updata(delta);
			player2->on_updata(delta);
			prop_manager->on_updata(delta);
		}
		
	}
	void on_draw()
	{
		putimage_alpha(pos_sky.x, pos_sky.y, &img_sky, &main_camera);
		putimage_alpha(pos_hills.x, pos_hills.y, &img_hills, &main_camera);
		for (size_t i = 0; i < list_platform.size(); i++)
		{
			list_platform.at(i).on_draw(main_camera);
		}
		if (is_debug)
		{
			settextcolor(RED);
			outtextxy(0, 150, L"调试模式已开启,按Q关闭");

		}
		else
		{
			settextcolor(WHITE);
		}
		if (!cursor_timeout)
		{
			putimage_alpha(player1->get_pos_center().x - size_cursor.x / 2, player1->get_pos_center().y - size_cursor.y - 50, &img_cursor_1P);
			putimage_alpha(player2->get_pos_center().x - size_cursor.x / 2, player2->get_pos_center().y - size_cursor.y - 50, &img_cursor_2P);

		}
		player1->on_draw(main_camera);
		player2->on_draw(main_camera);
		prop_manager->on_draw(main_camera);
		//分离子弹和玩家的渲染,画面表现更真实
		player1->damage_objects_draw(main_camera);
		player2->damage_objects_draw(main_camera);
		//血条和能量条的渲染
		draw_blood_energy(player1->get_blood(), player1->get_energy(), player2->get_blood(), player2->get_energy());
		//特殊技能数量渲染
		draw_ultra_skill(player1, player2);
		//游戏结束判定
		if (game_over)
		{
			mciSendString(L"stop bgm_game", NULL, 0, NULL);
			putimage_alpha((window_size.x - img_winner_bar.getwidth()) / 2-1080*(1-percent_over_tie), (window_size.y - img_winner_bar.getheight()) / 2, &img_winner_bar);
			if(winner_id==1)putimage_alpha((window_size.x - img_1P_winner.getwidth()) / 2 - 1080 *(1- percent_over_tie), (window_size.y - img_1P_winner.getheight()) / 2, &img_1P_winner);
			else putimage_alpha((window_size.x - img_2P_winner.getwidth()) / 2-1080*(1-percent_over_tie), (window_size.y - img_2P_winner.getheight()) / 2, &img_2P_winner);
		}
	}
	void draw_ultra_skill(Player* p1, Player* p2)
	{
		int n1=p1->get_ultraSkill_num();
		int n2 = p2->get_ultraSkill_num();
		for (size_t i = 0; i < n1; i++)
		{
			putimage_alpha(window_size.x * 1 / 5 + i * 80, window_size.y * 4 / 5 + 100, &img_coins);
		}
		for (size_t i = 0; i < n2; i++)
		{
			putimage_alpha(window_size.x * 3 / 5 + i * 80, window_size.y * 4 / 5 + 100, &img_coins);
		}
	}
	void draw_blood_energy(int b1, int e1, int b2, int e2)
	{
		switch (p1_character)
		{
		case Player::playerCharacter::sunflower:
			putimage_alpha(window_size.x * 1 / 10, window_size.y * 4 / 5,&img_sunflower_head);
			break;
		case Player::playerCharacter::peashoooter:
			putimage_alpha(window_size.x * 1 / 10, window_size.y * 4 / 5, &img_peashooter_head);
			break;
		case Player::playerCharacter::ninja:
			putimage_alpha(window_size.x * 1 / 10, window_size.y * 4 / 5, &img_ninja_head);
			break;
		default:
			break;
		}
		setfillcolor((45, 45, 45));
		fillroundrect(window_size.x * 1 / 5, window_size.y * 4 / 5, window_size.x * 1 / 5 + 300, window_size.y * 4 / 5 + 40,10,10);
		setfillcolor(RED);
		fillroundrect(window_size.x * 1 / 5, window_size.y * 4 / 5, window_size.x * 1 / 5 + b1 * bar_chip_length, window_size.y * 4 / 5 + 40,10,10);
		setfillcolor((45, 45, 45));
		fillroundrect(window_size.x * 1 / 5, window_size.y * 4 / 5+50, window_size.x * 1 / 5 + 300, window_size.y * 4 / 5 + 90, 10, 10);
		setfillcolor(BLUE);
		fillroundrect(window_size.x * 1 / 5, window_size.y * 4 / 5 + 50, window_size.x * 1 / 5 + e1 * bar_chip_length, window_size.y * 4 / 5 + 90,10,10);

		switch (p2_character)
		{
		case Player::playerCharacter::sunflower:
			putimage_alpha(window_size.x * 1 / 2, window_size.y * 4 / 5,  &img_sunflower_head);
			break;
		case Player::playerCharacter::peashoooter:
			putimage_alpha(window_size.x * 1 / 2, window_size.y * 4 / 5, &img_peashooter_head);
			break;
		case Player::playerCharacter::ninja:
			putimage_alpha(window_size.x * 1 / 2, window_size.y * 4 / 5, &img_ninja_head);
			break;
		default:
			break;
		}
		setfillcolor((45, 45, 45));
		fillroundrect(window_size.x * 3 / 5, window_size.y * 4 / 5, window_size.x * 3 / 5 + 300, window_size.y * 4 / 5 + 40,10,10);
		setfillcolor(RED);
		fillroundrect(window_size.x * 3 / 5, window_size.y * 4 / 5, window_size.x * 3 / 5 + b2 * bar_chip_length, window_size.y * 4 / 5 + 40,10,10);
		setfillcolor((45, 45, 45));
		fillroundrect(window_size.x * 3 / 5, window_size.y * 4 / 5+50, window_size.x * 3 / 5 + 300, window_size.y * 4 / 5 + 90, 10, 10);
		setfillcolor(BLUE);
		fillroundrect(window_size.x * 3 / 5, window_size.y * 4 / 5 + 50, window_size.x * 3 / 5 + e2 * bar_chip_length, window_size.y * 4 / 5 + 90,10,10);
	}
	void on_exit()
	{
		game_over = false;
		delete player1;
		delete player2;
		delete prop_manager;
	}

private:
	int winner_id = 1;//胜利玩家id:1/2
	Player::playerCharacter p1_character = Player::playerCharacter::sunflower;
	Player::playerCharacter p2_character = Player::playerCharacter::peashoooter;
	bool game_over = false;//游戏结束标志
	Winner winner = Winner::no_winner;//赢得胜利玩家
	int bar_chip_length = 3;//血量能量显示条每1%显示长度
	POINT pos_hills = { 0,0 };
	POINT pos_sky = { 0,0 };
	Timer timer_cursor_view;//光标显示时间计时
	POINT size_cursor = { 0,0 };//光标尺寸便于渲染定位
	bool cursor_timeout = false;//光标计时结束标志
	PropManager* prop_manager;//道具管理器
	Timer timer_prop_generate;//道具生成计时器
	float speed_over_tie=0.05;//游戏结束提示进入速度
	float percent_over_tie = 0;//结束显示进度
};

