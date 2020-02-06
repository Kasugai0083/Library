#pragma once

#include "..//Engine/Device.h"
#include "../Engine/Graphics/DirectX.h"
#include "SceneID.h"


#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


/**
* @brief 
* �V�[���̊��N���X
*/

class SceneBase {
public:

	//!< �R���X�g���N�^
	SceneBase() {
		m_State = SceneState::INIT;
	}
	virtual ~SceneBase() {}	//!< �f�X�g���N�^

	virtual void Init() = 0; //!< ����������

	virtual void Update() = 0; //!< �X�V����

	//!< �I������
	virtual SceneID End() {
		return SceneID::UNKNOWN;
	}
	
	virtual void Draw() {}; //!< �`�揈��

	/**
	* @brief ��ԑJ�ڏ���
	* @return ���̃V�[��ID��Ԃ�
	*/
	virtual SceneID Control() {
		return SceneID::UNKNOWN;
	}


protected:
	SceneState m_State;

};