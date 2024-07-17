#pragma once
#include"Scene.h"
#include"SceneManager.h"
#include"GameScene.h"
#include"PeaShooter.h"
#include"SunFlower.h"
extern SceneManager scene_manager;
extern const POINT window_size;
extern IMAGE img_select_scene_background;
extern IMAGE img_start_game_tip;
extern IMAGE img_start_game_tip_black;
extern IMAGE img_character_table;
extern IMAGE img_character_table_flipped;
extern IMAGE img_1P;
extern IMAGE img_1P_black;
extern IMAGE img_2P;
extern IMAGE img_2P_black;
extern IMAGE img_1P_selector_btn_right;
extern IMAGE img_1P_selector_btn_right_down;
extern IMAGE img_1P_selector_btn_left;
extern IMAGE img_1P_selector_btn_left_down;
extern IMAGE img_2P_selector_btn_right;
extern IMAGE img_2P_selector_btn_right_down;
extern IMAGE img_2P_selector_btn_left;
extern IMAGE img_2P_selector_btn_left_down;
extern IMAGE img_vs;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_idle_left;
extern IMAGE img_1P_desc;
extern IMAGE img_2P_desc;
extern Player* player1;
extern Player* player2;
class SelectScene : public Scene
{
public:
	enum Character
	{
		peashooter,
		sunflower,
		countnum
	};
	SelectScene() {}
	~SelectScene() {}
	void outtextxy_shaded(int x, int y, LPCTSTR s)
	{
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, s);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, s);
	}
	void on_enter()
	{
		pos_start_game_tip.x = (window_size.x - img_start_game_tip.getwidth()) / 2;
		pos_start_game_tip.y = window_size.y * 4 / 5;
		pos_table.x = (window_size.x - img_character_table.getwidth() * 2) / 6;
		pos_table.y = window_size.y * 1 / 5;
		pos_table_flipped.x = (window_size.x - pos_table.x - img_character_table.getwidth());
		pos_table_flipped.y = pos_table.y;
		pos_1P.x = pos_table.x + (img_character_table.getwidth() - img_1P.getwidth()) / 2;
		pos_1P.y = pos_table.y - img_1P.getheight()*3/2;
		pos_2P.x = pos_table_flipped.x + (img_character_table.getwidth() - img_1P.getwidth()) / 2;
		pos_2P.y = pos_1P.y;
		pos_1P_selector_btn_left.x = pos_table.x - img_1P_selector_btn_left.getwidth();
		pos_1P_selector_btn_left.y = pos_table.y + img_character_table.getheight() * 3 / 10;
		pos_1P_selector_btn_right.x = pos_table.x + img_character_table.getwidth();
		pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_left.x = pos_table_flipped.x - img_2P_selector_btn_left.getwidth();
		pos_2P_selector_btn_left.y = pos_table_flipped.y + img_character_table.getheight() * 3 / 10;
		pos_2P_selector_btn_right.x = pos_table_flipped.x + img_character_table.getwidth();
		pos_2P_selector_btn_right.y = pos_2P_selector_btn_left.y;
		pos_vs.x = (window_size.x - img_vs.getwidth()) / 2;
		pos_vs.y = (window_size.y - img_vs.getheight()) / 2;
		pos_1P_desc.x = pos_table.x;
		pos_1P_desc.y = pos_table.y + img_character_table.getheight() * 5 / 4;
		pos_2P_desc.x = pos_table_flipped.x;
		pos_2P_desc.y = pos_table_flipped.y + img_character_table.getheight() * 5 / 4;

		//按钮时间计时器
		timer_btn_down.set_wait_time(100);
		timer_btn_down.set_one_shot(true);
		timer_btn_down.set_callback([&]() {
			btn_1P_left_down = false;
			btn_1P_right_down = false;
			btn_2P_left_down = false;
			btn_2P_right_down = false;
			});
		//加入动画
		animation_1P_peashooter.set_atlas(&atlas_peashooter_idle_right);
		animation_1P_peashooter.set_interval(200);
		animation_1P_peashooter.set_loop(true);
		animation_1P_sunflower.set_atlas(&atlas_sunflower_idle_right);
		animation_1P_sunflower.set_interval(200);
		animation_1P_sunflower.set_loop(true);
		animation_2P_peashooter.set_atlas(&atlas_peashooter_idle_left);
		animation_2P_peashooter.set_interval(200);
		animation_2P_peashooter.set_loop(true);
		animation_2P_sunflower.set_atlas(&atlas_sunflower_idle_left);
		animation_2P_sunflower.set_interval(200);
		animation_2P_sunflower.set_loop(true);

		pos_1P_animation.x = pos_table.x + (img_character_table.getwidth() - atlas_peashooter_idle_right.get_img_at(0)->getwidth()) / 2;
		pos_1P_animation.y = pos_table.y + pos_table.y * 2/ 3;
		pos_2P_animation.x = pos_table_flipped.x + (img_character_table.getwidth() - atlas_peashooter_idle_left.get_img_at(0)->getwidth()) / 2;
		pos_2P_animation.y = pos_1P_animation.y;

		pos_text_1P.x = pos_1P_animation.x + 20;
		pos_text_1P.y = pos_1P_animation.y + 120;
		pos_text_2P.x = pos_2P_animation.x + 20;
		pos_text_2P.y = pos_2P_animation.y + 120;
	}
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_LBUTTONDOWN)//鼠标点击更新按钮按下状态 计时启动
		{

			if (msg.x >= pos_1P_selector_btn_left.x && msg.x <= pos_1P_selector_btn_left.x + img_1P_selector_btn_left.getwidth() &&
				msg.y >= pos_1P_selector_btn_left.y && msg.y <= pos_1P_selector_btn_left.y + img_1P_selector_btn_left.getheight())
			{
				btn_1P_left_down = true;
				character_1P = (enum Character)(((int)character_1P-1+countnum)%countnum);
				timer_btn_down.restart();
				mciSendString(L"play btn from 0", NULL, 0, NULL);
			}
			else
			{
				btn_1P_left_down = false;
			}

			if (msg.x >= pos_1P_selector_btn_right.x && msg.x <= pos_1P_selector_btn_right.x + img_1P_selector_btn_right.getwidth() &&
				msg.y >= pos_1P_selector_btn_right.y && msg.y <= pos_1P_selector_btn_right.y + img_1P_selector_btn_right.getheight())
			{
				btn_1P_right_down = true;
				character_1P = (enum Character)(((int)character_1P + 1 + countnum) % countnum);
				timer_btn_down.restart();
				mciSendString(L"play btn from 0", NULL, 0, NULL);
			}
			else
			{
				btn_1P_right_down = false;
			}

			if (msg.x >= pos_2P_selector_btn_left.x && msg.x <= pos_2P_selector_btn_left.x + img_2P_selector_btn_left.getwidth() &&
				msg.y >= pos_2P_selector_btn_left.y && msg.y <= pos_2P_selector_btn_left.y + img_2P_selector_btn_left.getheight())
			{
				btn_2P_left_down = true;
				character_2P = (enum Character)(((int)character_2P - 1 + countnum) % countnum);
				timer_btn_down.restart();
				mciSendString(L"play btn from 0", NULL, 0, NULL);
			}
			else
			{
				btn_2P_left_down = false;
			}

			if (msg.x >= pos_2P_selector_btn_right.x && msg.x <= pos_2P_selector_btn_right.x + img_2P_selector_btn_right.getwidth() &&
				msg.y >= pos_2P_selector_btn_right.y && msg.y <= pos_2P_selector_btn_right.y + img_2P_selector_btn_right.getheight())
			{
				btn_2P_right_down = true;
				character_2P = (enum Character)(((int)character_2P + 1 + countnum) % countnum);
				timer_btn_down.restart();
				mciSendString(L"play btn from 0", NULL, 0, NULL);
			}
			else
			{
				btn_2P_right_down = false;
			}
		}
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{  
			//"Enter"
			case 13:
				scene_manager.switch_to(SceneManager::sceneType::Game);
			default:
				break;
			}
		}
		
	}
	void on_updata(int delta)
	{
		timer_btn_down.on_updata(delta);
		switch (character_1P)
		{
		case SelectScene::peashooter:
			animation_1P_peashooter.on_updata(delta);
			break;
		case SelectScene::sunflower:
			animation_1P_sunflower.on_updata(delta);
			break;
		case SelectScene::countnum:
			break;
		default:
			break;
		}
		switch (character_2P)
		{
		case SelectScene::peashooter:
			animation_2P_peashooter.on_updata(delta);
			break;
		case SelectScene::sunflower:
			animation_2P_sunflower.on_updata(delta);
			break;
		case SelectScene::countnum:
			break;
		default:
			break;
		}
	}
	void on_draw()
	{
		putimage_alpha(0, 0, &img_select_scene_background);
		putimage_alpha(pos_vs.x, pos_vs.y, &img_vs);
		putimage_alpha(pos_start_game_tip.x + 3, pos_start_game_tip.y + 3, &img_start_game_tip_black);
		putimage_alpha(pos_start_game_tip.x, pos_start_game_tip.y, &img_start_game_tip);
		putimage_alpha(pos_table.x, pos_table.y, &img_character_table);
		putimage_alpha(pos_table_flipped.x, pos_table_flipped.y, &img_character_table_flipped);
		putimage_alpha(pos_1P.x + 5, pos_1P.y + 5, &img_1P_black);
		putimage_alpha(pos_1P.x, pos_1P.y, &img_1P);
		putimage_alpha(pos_2P.x + 5, pos_2P.y + 5, &img_2P_black);
		putimage_alpha(pos_2P.x, pos_2P.y, &img_2P);
		putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y, btn_1P_left_down ? &img_1P_selector_btn_left_down : &img_1P_selector_btn_left);
		putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y, btn_1P_right_down ? &img_1P_selector_btn_right_down : &img_1P_selector_btn_right);
		putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y, btn_2P_left_down ? &img_2P_selector_btn_left_down : &img_2P_selector_btn_left);
		putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y, btn_2P_right_down ? &img_2P_selector_btn_right_down : &img_2P_selector_btn_right);
		putimage_alpha(pos_1P_desc.x, pos_1P_desc.y, &img_1P_desc);
		putimage_alpha(pos_2P_desc.x, pos_2P_desc.y, &img_2P_desc);
		
		switch (character_1P)
		{
		case SelectScene::peashooter:
			animation_1P_peashooter.on_draw(pos_1P_animation.x,pos_1P_animation.y);
			outtextxy_shaded(pos_text_1P.x, pos_text_1P.y, text_peashooter);
			break;
		case SelectScene::sunflower:
			animation_1P_sunflower.on_draw(pos_1P_animation.x, pos_1P_animation.y);
			outtextxy_shaded(pos_text_1P.x, pos_text_1P.y, text_sunflower);
			break;
		case SelectScene::countnum:
			break;
		default:
			break;
		}
		switch (character_2P)
		{
		case SelectScene::peashooter:
			animation_2P_peashooter.on_draw(pos_2P_animation.x,pos_2P_animation.y);
			outtextxy_shaded(pos_text_2P.x, pos_text_2P.y, text_peashooter);
			break;
		case SelectScene::sunflower:
			animation_2P_sunflower.on_draw(pos_2P_animation.x, pos_2P_animation.y);
			outtextxy_shaded(pos_text_2P.x, pos_text_2P.y, text_sunflower);
			break;
		case SelectScene::countnum:
			break;
		default:
			break;
		}
	}
	void on_exit()
	{
		mciSendString(L"stop bgm_menu", NULL, 0, NULL);
		switch (character_1P)
		{
		case SelectScene::peashooter:
			player1 = new PeaShooter();
			break;
		case SelectScene::sunflower:
			player1 = new SunFlower();
			break;
		case SelectScene::countnum:
			break;
		default:
			break;
		}
		switch (character_2P)
		{
		case SelectScene::peashooter:
			player2 = new PeaShooter();
			break;
		case SelectScene::sunflower:
			player2 = new SunFlower();
			break;
		case SelectScene::countnum:
			break;
		default:
			break;
		}
		player1->set_id(1);
		player1->init_pos();
		player2->set_id(2);
		player2->init_pos();
	}

private:
	POINT pos_start_game_tip = { 0,0 };
	POINT pos_table = { 0,0 };
	POINT pos_table_flipped = { 0,0 };
	POINT pos_1P = { 0,0 };
	POINT pos_2P = { 0,0 };
	POINT pos_1P_selector_btn_right = { 0,0 };
	POINT pos_1P_selector_btn_left = { 0,0 };
	POINT pos_2P_selector_btn_right = { 0,0 };
	POINT pos_2P_selector_btn_left = { 0,0 };
	POINT pos_vs = { 0,0 };
	POINT pos_1P_animation = { 0,0 };
	POINT pos_2P_animation = { 0,0 };
	POINT pos_1P_desc = { 0,0 };
	POINT pos_2P_desc = { 0,0 };
	POINT pos_text_1P = { 0,0 };
	POINT pos_text_2P = { 0,0 };
	bool btn_1P_left_down = false;
	bool btn_1P_right_down = false;
	bool btn_2P_left_down = false;
	bool btn_2P_right_down = false;
	Timer timer_btn_down;
	Animation animation_1P_sunflower;
	Animation animation_1P_peashooter;
	Animation animation_2P_sunflower;
	Animation animation_2P_peashooter;
	Character character_1P = sunflower;
	Character character_2P = peashooter;
	LPCTSTR text_peashooter=L"豌豆射手";
	LPCTSTR text_sunflower=L"向日葵";
};
