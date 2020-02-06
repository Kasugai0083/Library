#pragma once

#include "..//..//Utility/Vec2.h"
#include "..//..//Utility/Vec3.h"
#include "..//..//Utility/Size.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <map>
#include <vector>

/**
* @brief
* 2D�|���S���p�̉摜��ۑ��E�`�悷��N���X
*/

struct LineDesc;


/**
* Texture �̃f�[�^�ƃT�C�Y���Ǘ�����\����
*/
struct Texture{
	LPDIRECT3DTEXTURE9 TexutreData;		//!< �e�N�X�`���f�[�^
	float Width;						//!< ����
	float Height;						//!< �c��
};

/**
* @brief �|���S���`��ɕK�v�Ȓ��_���
* @param pos ���W
* @param tex_pos �e�N�X�`�����W
*/
struct CustomVertex {

	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex_pos;

};

/**
* @brief �|���S���`��ɕK�v�Ȓ��_���
* @param pos ���W
* @param tex_pos_start �e�N�X�`�����W�J�n�_
* @param tex_pos_end �e�N�X�`�����W�I���_
*/
struct VertexPos {

	Pos3 pos;
	Pos2 tex_pos_start, tex_pos_end;

};

class Drawer2D
{
public:

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
	* @brief DrawTextA �Ńe�L�X�g��\��\n
	* DrawTextA �̓s����AZ���͐ݒ�ł��Ȃ�
	* @param pos_ �e�L�X�g�̍��W
	* @param text_ �e�L�X�g�̓��e
	*/
	void DrawFont(Vec2 pos_, std::string text_);

	/**
	* @brief �w�肵���e�N�X�`���̈�����
	* @param �̈���w��
	*/
	void Release(std::string file_name_);

private:
	/**
	* @brief m_TextureList �Ƀe�N�X�`���������
	* @param file_name_ �v�f�ԍ����w��
	*/
	bool CreateTexture(std::string file_name_);

	void DrawSetting(float x_, float y_, float z_); //!< @brief DirectX�̃f�o�C�X �� �s����̏�����

private:

	std::map<std::string, Texture*>m_TextureList; //!< @brief �摜����ۊ�

};