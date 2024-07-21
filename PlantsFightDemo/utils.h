#pragma once
#include<graphics.h>
#include"Camera.h"
#pragma comment(lib,"MSIMG32.LIB")
inline void flip_image(IMAGE* src, IMAGE* dst)//图片翻转
{
	int src_width = src->getwidth();
	int src_height = src->getheight();
	dst->Resize(src_width, src_height);
	DWORD* src_img_buffer = GetImageBuffer(src);
	DWORD* dst_img_buffer = GetImageBuffer(dst);
	//像素处理过程
	for (size_t i = 0; i < src_height; i++)
	{
		for (size_t j = 0; j < src_width; j++)
		{
			int temp = src_width - 1 - j;
			dst_img_buffer[i * src_width + temp] = src_img_buffer[i * src_width + j];

		}
	}
}
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int h = img->getheight();
	int w = img->getwidth();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
inline void putimage_alpha(int x, int y, IMAGE* img,Camera* camera)
{
	int h = img->getheight();
	int w = img->getwidth();

	AlphaBlend(GetImageHDC(GetWorkingImage()), x-(int)(camera->get_position().x), y- (int)(camera->get_position().y), w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
inline void black_image(IMAGE* src, IMAGE* dst)
{
	int src_width = src->getwidth();
	int src_height = src->getheight();
	dst->Resize(src_width, src_height);
	DWORD* src_img_buffer = GetImageBuffer(src);
	DWORD* dst_img_buffer = GetImageBuffer(dst);
	//像素处理过程
	BYTE r = NULL;
	BYTE g = NULL;
	BYTE b = NULL;
	BYTE alpha = NULL;
	for (size_t i = 0; i < src_height; i++)
	{
		for (size_t j = 0; j < src_width; j++)
		{
			b = GetRValue(src_img_buffer[i * src_width + j]);
			g = GetGValue(src_img_buffer[i * src_width + j]);
			r = GetBValue(src_img_buffer[i * src_width + j]);
			alpha = (src_img_buffer[i * src_width + j] & 0xFF000000) >> 24;
			dst_img_buffer[i * src_width + j] = (DWORD)(BLACK) | alpha << 24;
		}
	}
}
inline float get_distance(Vector2 v1, Vector2 v2)
{
	return sqrt((v1.x-v2.x)* (v1.x - v2.x)+ (v1.y - v2.y) * (v1.y - v2.y));
}