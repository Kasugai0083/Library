#ifndef SLIDER_H_
#define SLIDER_H_

#include "DirectX.h"

/** @brief �X���C�_�[�̈ړ����� */
enum Direction
{
	LeftToRight,		//!< �� => �E
	RightToLeft,		//!< �E => ��
	UpToDown,			//!< �� => ��
	DownToUp,			//!< �� => ��
};

enum SliderTextureList
{
	Slider01Texture = 10,	//!< �X���C�_�[(���E��)
	Slider02Texture,	//!< �X���C�_�[(�㉺��)
	SliderTextureMax
};

/** @brief �X���C�_�[�\���� */
struct Slider
{

	// ���㌴�_
	float X;				//!< �X���C�_�[�`��ʒu(X)
	float Y;				//!< �X���C�_�[�`��ʒu(Y)

	float MinValue;			//!< �ŏ��l
	float MaxValue;			//!< �ő�l

	float CurrentValue;		//!< ���݂̒l
	float NextValue;		//!< ���̒l
	float MoveSpeed;		//!< �ړ����x

	Direction Dir;			//!< �i�s����
	int Texture;	//!< �g�p����e�N�X�`��
};

void UpdateSliderNextValue(float next_value, Slider& out_slider);

void UpdateSliderCurrentValue(Slider& out_slider);

void ReverseMove(float rate, float size, float& out_pos, float& out_tex_pos, float& out_size);

void DrawSliderRectVersion(const Slider& slider);

void DrawSliderUVMappingVersion(const Slider& slider);

#endif