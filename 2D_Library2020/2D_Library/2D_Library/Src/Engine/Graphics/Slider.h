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
	LEFT_TO_RIGHT,
	RIGHT_TO_LEFT
};

/**
* @brief �X���C�_�[�̃X�e�[�^�X
*/
struct t_SilderState {
	int count;				//!< @brief �o�߃t���[����ۑ�

	float x;				//!< @brief �X���C�_�[�`��ʒu(X)
	float y;				//!< @brief �X���C�_�[�`��ʒu(Y)
	float z;				//!< @brief �X���C�_�[�`��ʒu(Z)

	float min_value;			//!< @brief �ŏ��l
	float max_value;			//!< @brief �ő�l

	float current_value;		//!< @brief ���݂̒l
	float next_value;		//!< @brief ���̒l
	float move_speed;		//!< @brief �ړ����x

	Direction dir;			//!< @brief �i�s����
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
	Slider(Pos3 pos_,Direction dir_)
	{
		m_slider_sta.count = 0;
		m_slider_sta.x = pos_.x;
		m_slider_sta.y = pos_.y;
		m_slider_sta.z = pos_.z;
		m_slider_sta.min_value = 0.f;
		m_slider_sta.max_value = 100.f;
		m_slider_sta.current_value = 0.f;
		m_slider_sta.next_value = 100.f;
		m_slider_sta.move_speed = 0.f;
		m_slider_sta.dir = dir_;
	}

	/**
	* @brief Drawer2D��p���ĉ摜��ǂݍ���
	*/
	void Load(std::string fileName_) {	m_drawer2d.LoadTexture(fileName_);}

	/**
	* @brief �X���C�_�[�̍X�V\n
	* �X���C�_�[�̃X�e�[�^�X���Q�Ƃ��đ��������肷��
	*/
	void Update();

	void DrawSlider(std::string fileName_);

	void Release(std::string fileName_) {	m_drawer2d.Release(fileName_); }

private:
	/**
	* @brief Update() ���Ŏg�p�����֐�
	*/
	void UpdateNextSliderValue(bool plus_);
	void UpdateSliderCurrentValue();

private:
	t_SilderState m_slider_sta;

	Drawer2D m_drawer2d;		//!< @brief �`��p�̊֐����Ăяo��

};
