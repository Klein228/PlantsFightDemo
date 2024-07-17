#pragma once
#include"Player.h"
#include"Animation.h"
extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_die_right;
extern Atlas atlas_peashooter_attack_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_die_left;
extern Atlas atlas_peashooter_attack_left;
class PeaShooter:public Player
{
public:
	PeaShooter()
	{
		this->run_speed = 3;
		animation_player_idle_left.set_atlas(&atlas_peashooter_idle_left);
		animation_player_idle_left.set_interval(100);
		animation_player_idle_left.set_loop(true);
		animation_player_idle_right.set_atlas(&atlas_peashooter_idle_right);
		animation_player_idle_right.set_interval(100);
		animation_player_idle_right.set_loop(true);

		animation_player_run_left.set_atlas(&atlas_peashooter_run_left);
		animation_player_run_left.set_interval(100);
		animation_player_run_left.set_loop(true);
		animation_player_run_right.set_atlas(&atlas_peashooter_run_right);
		animation_player_run_right.set_interval(100);
		animation_player_run_right.set_loop(true);

		animation_player_die_left.set_atlas(&atlas_peashooter_die_left);
		animation_player_die_left.set_interval(100);
		animation_player_die_left.set_loop(true);
		animation_player_die_right.set_atlas(&atlas_peashooter_die_right);
		animation_player_die_right.set_interval(100);
		animation_player_die_right.set_loop(true);

		animation_player_attack_left.set_atlas(&atlas_peashooter_attack_left);
		animation_player_attack_left.set_interval(100);
		animation_player_attack_left.set_loop(false);
		animation_player_attack_right.set_atlas(&atlas_peashooter_attack_right);
		animation_player_attack_right.set_interval(100);
		animation_player_attack_right.set_loop(false);
	};
	~PeaShooter() {};

	void on_input(const ExMessage& msg)
	{
	
		Player::on_input(msg);

	}
	void on_updata(int delta)
	{
		Player::on_updata(delta);
	}
	void on_draw(Camera& camera)
	{
		Player::on_draw(camera);
	}

private:

};
