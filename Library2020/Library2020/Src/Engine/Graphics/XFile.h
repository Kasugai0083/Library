#pragma once

#include "DirectX.h"
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

/**
* @brief 
* XFile ���Ǘ�����N���X
* !���̃N���X�̓Q�[�����[�v�ŃC���X�^���X�����܂���!
*/

class XFile
{
public:

	/**
	* @brief �R���X�g���N�^\n
	* �����o�ϐ�������������
	*/
	XFile() :
		m_material_num(0),
		m_mesh(NULL),
		m_mesh_material_list(NULL),
		m_ptr_tex_list(NULL)
	{
	}

	/**
	* @brief �f�X�g���N�^\n
	* �ۑ����� XFile ����j������
	*/
	~XFile();

	/**
	* @brief XFile ��ǂݍ���
	* @param XFile �̃p�X���w�肷��\n
	* �ǂݍ��܂ꂽ XFile �� m_pFileList �ɕۑ�
	*/
	bool Load(std::string fileName_);

	/**
	* @brief �ǂݍ��܂ꂽ XFile ���Ɋ�Â��ĕ`��\n
	* XFileDrawer �N���X�ŌĂяo�����
	*/
	void Draw();

private:
	/**
	* @brief XFile ��ǂݍ��񂾍ۂɃ}�e���A������ۊ�
	*/
	DWORD m_material_num;
	D3DMATERIAL9* m_mesh_material_list;

	/**
	* @brief XFile ��ǂݍ��񂾍ۂɃ��b�V������ۊ�
	*/
	LPD3DXMESH m_mesh;

	/**
	* @brief XFile ��ǂݍ��񂾍ۂɃe�N�X�`������ۊ�
	*/
	LPDIRECT3DTEXTURE9* m_ptr_tex_list;
	std::map<std::string, LPDIRECT3DTEXTURE9> m_tex_list;
	std::map<int, std::string> m_tex_name_list;

	/**
	* @brief XFile �̏���ۊ� 
	*/
	std::map<std::string, XFile*> m_xfile_list;

};

