#pragma once

#include "DirectX.h"
#include "XFile.h"
#include <d3d9.h>
#include <d3dx9.h>

/**
* @brief
* XFile ��`�悷��N���X
*/

class XFile;

class XFileDrawer
{
public:

	/**
	* @brief XFile ��`�悷��
	* @param pos_ �I�u�W�F�N�g�̍��W 
	* @param scale_  �I�u�W�F�N�g�̊g�k
	* @param angle_  �I�u�W�F�N�g�̉�]
	* @param name_  �I�u�W�F�N�g�̖��O
	*/
	void Draw(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);

	/**
	* @brief XFile ���r���{�[�h��K�p���ĕ`�悷��
	* @param pos_ �I�u�W�F�N�g�̍��W
	* @param scale_  �I�u�W�F�N�g�̊g�k
	* @param angle_  �I�u�W�F�N�g�̉�]
	* @param name_  �I�u�W�F�N�g�̖��O
	*/
	void DrawBillbord(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);

	/**
	* @brief XFile ��ǂݍ���
	* @param name_ XFile �̖��O���w��
	*/
	bool Load(std::string name_);

	/**
	* @brief �ǂݍ��� XFile �����
	*/
	void ReleaseXFile() {
		m_pXFileList.clear();
	}

private:
	/**
	* @brief Draw() �̓��Ŏg�p\n
	* �ړ��E�g�k�E��]���֐���p���Čv�Z����
	*/
	void Trans(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_);
private:
	D3DXVECTOR3 m_Pos, m_Scale, m_Angle; 								//!< @brief �I�u�W�F�N�g���

	D3DXMATRIX world_matrix, trans_matrix, view_matrix; 				//!< @brief ���W�n�̍s��

	D3DXMATRIX rot_matrix_x, rot_matrix_y, rot_matrix_z, rot_matrix; 	//!< @brief ��]�s��

	D3DXMATRIX scale_matrix; 											//!< @brief �g�k�s��

	std::map<std::string, XFile*> m_pXFileList; 						//!< @brief �摜�������X�g��

};

