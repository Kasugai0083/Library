#pragma once
#include "../SceneBase.h"
#include "../../Engine/Graphics/Grid.h"


/**
* @brief
* �Q�[�����C���̃V�[������
*/

//!< �Ȑ��̒ʉߓ_���w��
namespace {
	Vec3 start(-5.f, -1.f, 0.f);
	Vec3 center(10.f, 2.f, 0.f);
	Vec3 end(20.f, -2.f, 0.f);
}

class GameScene : public SceneBase
{
public:
	//!< �R���X�g���N�^
	GameScene() : 
		Gridman(start, center, end)
	{}
	~GameScene()override;		//!< �f�X�g���N�^
private:
	void Init()override;		//!< �V�[���̏�����
	void Update()override;		//!< �V�[���̍X�V
	SceneID End()override;		//!< �V�[���̉��
	SceneID Control()override;	//!< �V�[���̐���
	void Draw()override;		//!< �V�[���̕`��
private:
	Drawer2D drawer;			//!< �t�H���g�\���Ɏg�p
	LineDrawer Gridman;			//!< XFile�̕`��Ɏg�p
};
