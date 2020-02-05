#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/XFileDrawer.h"

/**
* @brief
* �^�C�g���V�[���̏���
*/

class TitleScene :public SceneBase
{
public:
	TitleScene();			//!< �R���X�g���N�^
	~TitleScene()override;	//!< �f�X�g���N�^

private:
	void Init()override;	//!< �V�[���̏�����
	void Update()override;	//!< �V�[���̍X�V
	SceneID End()override;	//!< �V�[���̉��
	SceneID Control();		//!< �V�[���̐���
	void Draw()override;	//!< �V�[���̕`��
private:

	Drawer2D drawer;		//!< �t�H���g�\���Ɏg�p
	XFileDrawer Object;		//!< XFile�̕`��Ɏg�p
};

