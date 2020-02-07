#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Slider.h"

/**
* @brief
* ���U���g�V�[���̏���
*/

namespace {
	Pos3 pos1(5.f, 5.f, 0.f);
	Pos3 pos2(0.f, 0.f, 10.f);
}

class ResultScene :public SceneBase
{
public:
	//!< �R���X�g���N�^
	ResultScene() : 
		m_slider1(pos1, Direction::LEFT_TO_RIGHT),
		m_slider2(pos2, Direction::RIGHT_TO_LEFT)
	{}
	~ResultScene()override;		//!< �f�X�g���N�^
private:
	void Init()override;		//!< �V�[���̏�����
	void Update()override;		//!< �V�[���̍X�V
	SceneID End()override;		//!< �V�[���̉��
	SceneID Control()override;	//!< �V�[���̐���
	void Draw()override;		//!< �V�[���̕`��
private:
	Drawer2D m_drawer2d;			//!< �t�H���g�\���Ɏg�p
	Drawer3D m_drawer3d;			//!< �t�H���g�\���Ɏg�p
	
	//!< �X���C�_�[�̕`��Ɏg�p
	Slider m_slider1;				
	Slider m_slider2;				 

};

