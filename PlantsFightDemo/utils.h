#pragma once
#include<graphics.h>
#pragma comment(lib,"MSIMG32.LIB")
inline void flip_image(IMAGE* src, IMAGE* dst)//图片翻转
{
	int src_width = src->getwidth();
	int src_height = src->getheight();
	dst->Resize(src_width, src_height);
	DWORD* src_img_buffer=GetImageBuffer(src);
	DWORD* dst_img_buffer = GetImageBuffer(dst);
	//像素处理过程
	for (size_t i = 0; i < src_height; i++)
	{
		int temp = src_width - 1;
		for (size_t j = 0; j < src_width; j++)
		{
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
