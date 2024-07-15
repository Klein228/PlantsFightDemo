#pragma once
#include"Scene.h"
#include"SceneManager.h"
extern SceneManager scene_manager;
extern IMAGE select_scene_background_img;
extern IMAGE table_img;
extern Atlas evilwizard3_attack_right_atlas;
class SelectScene : public Scene
{
public:
	SelectScene() {}
	~SelectScene() {}
	void on_enter()
	{
		evil_wizard_attack_right_animation.set_atlas(&evilwizard3_attack_right_atlas);
		evil_wizard_attack_right_animation.set_interval(100);
		evil_wizard_attack_right_animation.set_loop(true);

		character1_position.x = (table_position.x + (table_img.getwidth() - evilwizard3_attack_right_atlas.get_img_at(0)->getwidth()) / 2);
		character1_position.y = (table_position.y + (table_img.getheight() - evilwizard3_attack_right_atlas.get_img_at(0)->getheight()) / 2);
	}
	void on_input(const ExMessage& msg)
	{

	}
	void on_updata(int delta)
	{
		evil_wizard_attack_right_animation.on_updata(delta);
	}
	void on_draw()
	{
		putimage_alpha(0, 0, &select_scene_background_img);
		putimage_alpha(table_position.x, table_position.y, &table_img);
		putimage_alpha(getwidth()-table_position.x-table_img.getwidth(), table_position.y, &table_img);
		evil_wizard_attack_right_animation.on_draw(character1_position.x,character1_position.y);
		
	}
	void on_exit()
	{

	}

private:
	POINT table_position = {200,80};
	POINT character1_position = { 0,0 };
	Animation evil_wizard_attack_right_animation;
};
