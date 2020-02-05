#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Slider.h"

/**
* @brief
* ���U���g�V�[���̏���
*/
class ResultScene :public SceneBase
{
public:
	//!< �R���X�g���N�^
	ResultScene() : 
		slider1(5.f, 5.f, 0.f, Direction::LeftToRight),
		slider2(0.f, 0.f, 0.f, Direction::RightToLeft)
	{}
	~ResultScene()override;		//!< �f�X�g���N�^
private:
	void Init()override;		//!< �V�[���̏�����
	void Update()override;		//!< �V�[���̍X�V
	SceneID End()override;		//!< �V�[���̉��
	SceneID Control()override;	//!< �V�[���̐���
	void Draw()override;		//!< �V�[���̕`��
private:
	Drawer2D drawer;			//!< �t�H���g�\���Ɏg�p
	
	//!< �X���C�_�[�̕`��Ɏg�p
	Slider slider1;				
	Slider slider2;				 

};

