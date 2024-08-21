#pragma once
#include"Camera.h"
#include"utils.h"
extern bool is_debug;
class Platform
{
public:
	class ConstractShape {
	public:
		int y;
		int x_begin;
		int x_end;
	};
	ConstractShape shape;
	IMAGE* img=nullptr;
	POINT pos_render = { 0 };
public:
	Platform();
	~Platform();
	void on_draw(Camera camera)
	{
		putimage_alpha(pos_render.x, pos_render.y, img, &camera);
		if (is_debug)
		{
			Line(&camera);
		}
	}
	void Line(Camera *camera)
	{
		line(shape.x_begin-camera->get_position().x, shape.y-camera->get_position().y, shape.x_end- camera->get_position().x, shape.y- camera->get_position().y);
	}

private:
	
};

Platform::Platform()
{
}

Platform::~Platform()
{
}