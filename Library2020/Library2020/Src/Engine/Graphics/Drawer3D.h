#pragma once

#include "DirectX.h"
#include "XFile.h"
#include "Grid.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>

/**
* @brief
* XFile ��`�悷��N���X
*/


class Drawer3D
{
public:		//!< XFile�֘A���\�b�h


	/**
	* @brief XFile ��`�悷��
	* @param pos_ �I�u�W�F�N�g�̍��W 
	* @param scale_  �I�u�W�F�N�g�̊g�k
	* @param angle_  �I�u�W�F�N�g�̉�]
	* @param name_  �I�u�W�F�N�g�̖��O
	*/
	void DrawXFile(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);

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
	bool LoadXFile(std::string name_);

	/**
	* @brief �ǂݍ��� XFile �����
	*/
	void ReleaseXFile() {
		m_pXFileList.clear();
	}

public:		//!< �|���S���֘A���\�b�h

	/**
	* @brief �e�N�X�`����\��t�����|���S����`�悷��
	* @param v_ �|���S���̒��_��� �� �e�N�X�`���̍��W���
	* @param file_name_ m_TextureList �̗v�f
	*/
	void DrawTexture(VertexPos v_, std::string file_name_);

	/**
	* @brief m_TextureList �Ƀe�N�X�`���������\n
	* �ǂݍ��݂Ɏ��s�����ꍇ�A�G���[���b�Z�[�W��Ԃ�
	* @param file_name_ �v�f�ԍ����w��
	*/
	void LoadTexture(std::string file_name_) {
		if (!CreateTexture(file_name_)) {
			std::string msg = " �̓ǂݍ��݂Ɏ��s";
			std::string pop_msg = file_name_ + msg;

			MessageBox(NULL, pop_msg.c_str(), NULL, MB_OK);
		}
	}

	/**
	* @brief �Ȑ��̕`��
	* @param �Ȑ��̒��_���
	*/
	void DrawLine(std::vector<LineDesc> desc_list);

	/**
	* @brief �e�N�X�`�������擾
	* @return �e�N�X�`�����̃|�C���^��Ԃ�
	*/
	Texture* GetTexture(std::string file_name_) { return m_TextureList[file_name_]; }


	/**
	* @brief �w�肵���e�N�X�`���̈�����
	* @param �̈���w��
	*/
	void Release(std::string file_name_);



private:	//!< XFile�֘A���\�b�h

	/**
	* @brief Draw() �̓��Ŏg�p\n
	* �ړ��E�g�k�E��]���֐���p���Čv�Z����
	*/
	void Trans(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_);

private:	//!< �|���S���֘A���\�b�h

	/**
	* @brief m_TextureList �Ƀe�N�X�`���������
	* @param file_name_ �v�f�ԍ����w��
	*/
	bool CreateTexture(std::string file_name_);

	void DrawSetting(float x_, float y_, float z_); //!< @brief DirectX�̃f�o�C�X �� �s����̏�����

private:	//!< XFile�֘A�����o�ϐ�

	D3DXVECTOR3 m_Pos, m_Scale, m_Angle; 								//!< @brief �I�u�W�F�N�g���

	D3DXMATRIX world_matrix, trans_matrix, view_matrix; 				//!< @brief ���W�n�̍s��

	D3DXMATRIX rot_matrix_x, rot_matrix_y, rot_matrix_z, rot_matrix; 	//!< @brief ��]�s��

	D3DXMATRIX scale_matrix; 											//!< @brief �g�k�s��

	std::map<std::string, XFile*> m_pXFileList; 						//!< @brief �摜�������X�g��

private:	//!< �|���S���֘A�����o�ϐ�

	std::map<std::string, Texture*>m_TextureList; //!< @brief �摜����ۊ�

};

