#pragma once

#include "Drawer2D.h"
#include <string>

/**
* @brief
* �X���C�_�[���Ǘ��E�`�悷��N���X
*/

/**
* @enum ���������肷��񋓎q
*/
enum class Direction {
	LeftToRight,
	RightToLeft
};

class Slider {
public:
	
	/**
	* @brief �R���X�g���N�^
	* @param x_ �X���C�_�[��X���W
	* @param y_ �X���C�_�[��Y���W
	* @param z_ �X���C�_�[��Z���W
	* @param dir_ �X���C�_�[�̕���
	*/
	Slider(float x_, float y_, float z_,Direction dir_) :
		count(0),
		X(x_),
		Y(y_),
		Z(z_),
		MinValue(0.f),
		MaxValue(100.f),
		CurrentValue(0.f),
		NextValue(100.f),
		MoveSpeed(0.f),
		Dir(dir_)
	{}

	/**
	* @brief �X���C�_�[�̍X�V\n
	* �X���C�_�[�̃X�e�[�^�X���Q�Ƃ��đ��������肷��
	*/
	void Update();

	/**
	* @brief �X���C�_�[��`�悷��
	*/
	void DrawSlider(std::string file_name_);

private:
	/**
	* @brief Update() ���Ŏg�p�����֐�
	*/
	void UpdateNextSliderValue(bool plus_);
	void UpdateSliderCurrentValue();

private:
	int count;				//!< @brief �o�߃t���[����ۑ�

	float X;				//!< @brief �X���C�_�[�`��ʒu(X)
	float Y;				//!< @brief �X���C�_�[�`��ʒu(Y)
	float Z;				//!< @brief �X���C�_�[�`��ʒu(Z)

	float MinValue;			//!< @brief �ŏ��l
	float MaxValue;			//!< @brief �ő�l

	float CurrentValue;		//!< @brief ���݂̒l
	float NextValue;		//!< @brief ���̒l
	float MoveSpeed;		//!< @brief �ړ����x

	Direction Dir;			//!< @brief �i�s����

	Drawer2D InsDrawer;		//!< @brief �`��p�̊֐����Ăяo��

};

