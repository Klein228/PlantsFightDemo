#pragma once
#include<graphics.h>
#include"Camera.h"
#pragma comment(lib,"MSIMG32.LIB")
#pragma comment(lib,"WINMM.lib")
struct Rect
{
	int x, y;
	int w, h;
};
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
inline void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
{
	static BLENDFUNCTION blend_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };
	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0,
		rect_src ? rect_src->w : img->getwidth(), rect_src ? rect_src->h : img->getheight(), blend_func);
}
double AngleBetweenVectors(const Vector2& a, const Vector2& b) {
	double dotProduct = a.dot(b);
	double magnitudeA = a.length();
	double magnitudeB = b.length();

	// 检查除数是否为零以避免除以零的错误
	if (magnitudeA == 0 || magnitudeB == 0) {
		throw std::invalid_argument("One of the vectors has zero magnitude.");
	}

	// 计算夹角的余弦值
	double cosTheta = dotProduct / (magnitudeA * magnitudeB);

	// 确保余弦值在[-1, 1]范围内，以避免由于浮点数精度问题导致的误差
	cosTheta = cosTheta > 1.0 ? 1.0 : (cosTheta < -1.0 ? -1.0 : cosTheta);

	// 使用acos函数计算夹角
	return std::acos(cosTheta);
}
// 使用旋转矩阵顺时针旋转向量
Vector2 RotateVectorByMatrix(const Vector2& v, double angleInDegrees) {
	// 将角度转换为弧度
	double angleInRadians = angleInDegrees * (M_PI / 180.0);

	// 计算旋转矩阵的元素
	double cosTheta = std::cos(angleInRadians);
	double sinTheta = std::sin(angleInRadians);

	// 应用旋转矩阵
	Vector2 rotatedVector(
		cosTheta * v.x + sinTheta * v.y, // 新的x坐标
		-sinTheta * v.x + cosTheta * v.y  // 注意这里是sinTheta乘以原向量的x坐标
	);

	return rotatedVector;
}