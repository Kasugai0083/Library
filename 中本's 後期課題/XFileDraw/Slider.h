#ifndef SLIDER_H_
#define SLIDER_H_

#include "DirectX.h"

/** @brief スライダーの移動方向 */
enum Direction
{
	LeftToRight,		//!< 左 => 右
	RightToLeft,		//!< 右 => 左
	UpToDown,			//!< 上 => 下
	DownToUp,			//!< 下 => 上
};

enum SliderTextureList
{
	Slider01Texture = 10,	//!< スライダー(左右版)
	Slider02Texture,	//!< スライダー(上下版)
	SliderTextureMax
};

/** @brief スライダー構造体 */
struct Slider
{

	// 左上原点
	float X;				//!< スライダー描画位置(X)
	float Y;				//!< スライダー描画位置(Y)

	float MinValue;			//!< 最小値
	float MaxValue;			//!< 最大値

	float CurrentValue;		//!< 現在の値
	float NextValue;		//!< 次の値
	float MoveSpeed;		//!< 移動速度

	Direction Dir;			//!< 進行方向
	int Texture;	//!< 使用するテクスチャ
};

void UpdateSliderNextValue(float next_value, Slider& out_slider);

void UpdateSliderCurrentValue(Slider& out_slider);

void ReverseMove(float rate, float size, float& out_pos, float& out_tex_pos, float& out_size);

void DrawSliderRectVersion(const Slider& slider);

void DrawSliderUVMappingVersion(const Slider& slider);

#endif