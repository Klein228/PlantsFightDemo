#pragma once
#include"Atlas.h"
#include"utils.h"
#include"functional"
#include"Camera.h"
extern Camera main_camera;
class Animation
{
public:
	Animation() {}
	~Animation() {}
	void reset()
	{
		timer = 0;
		idx_frame = 0;
	}
	void set_atlas(Atlas* atl)
	{
		reset();
		atlas = atl;
	}
	void set_loop(bool loop)
	{
		is_loop = loop;
	}
	void set_interval(unsigned int ms)
	{
		this->interval = ms;
	}
	int get_index_frame()
	{
		return idx_frame;
	}
	IMAGE* get_frame()
	{
		return atlas->get_img_at(idx_frame);
	}
	bool check_finished()
	{
		if (is_loop)return false;
		return (idx_frame == atlas->get_size() - 1);
	}
	void on_updata(int delta)
	{
		timer += delta;
		if (timer >= interval)
		{
			timer = 0;
			if (idx_frame >= atlas->get_size() - 1)
			{
				idx_frame = (is_loop) ? 0 : atlas->get_size() - 1;
				if (!is_loop && callback)
				{
					callback();
				}
			}
			else
			{
				idx_frame++;
			}
		}
	}
	void on_draw(int x, int y)const
	{
		putimage_alpha(x, y, atlas->get_img_at(idx_frame),&main_camera);
	}
	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}
private:
	int timer = 0;			//计时器
	int interval = 0;		//帧间隔
	int idx_frame = 0;		//帧索引
	bool is_loop = true;	//是否循环播放动画
	Atlas* atlas = nullptr;
	std::function<void()> callback;
};