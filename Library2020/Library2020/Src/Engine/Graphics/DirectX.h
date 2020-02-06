#ifndef DIRECTX_H_
#define DIRECTX_H_

#include "../../Utility/SingletonTemplate.h"
#include "..//..//Utility/Size.h"
#include "../../Utility/Vec3.h"
#include "../../Utility/Vec2.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>

/**
* @brief 
* DirectX���������E�Ǘ�����N���X
*/

/**
* Texture �̃f�[�^�ƃT�C�Y���Ǘ�����\����
*/
struct t_Texture {
	LPDIRECT3DTEXTURE9 texture_data;		//!< �e�N�X�`���f�[�^
	float width;						//!< ����
	float height;						//!< �c��
};

/**
* @brief �|���S���`��ɕK�v�Ȓ��_���
* @param pos ���W
* @param tex_pos �e�N�X�`�����W
*/
struct t_CustomVertex {

	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex_pos;

};

/**
* @brief �|���S���`��ɕK�v�Ȓ��_���
* @param pos ���W
* @param tex_pos_start �e�N�X�`�����W�J�n�_
* @param tex_pos_end �e�N�X�`�����W�I���_
*/
struct t_VertexPos {

	Pos3 pos;
	Pos2 tex_pos_start, tex_pos_end;

};

/**
* @enum �e�`��֐��̕`�掟�������Ă�����̂Ɏg�p
*/
enum class Dimendion {
	DIMENSION_2,
	DIMENSION_3,
};

/**
* @brief DirextX�X�e�[�^�X�\����\n
* �󂯓n�����ȗ������邽�߂ɍ\���̂ɓZ�߂�
*/
struct t_DxStatus 
{
	LPDIRECT3D9 d3d_interface;	//!< @brief DirectX�C���^�[�t�F�[�X
	
	D3DPRESENT_PARAMETERS* d3d_present_param; //!< @brief DirectX�̐ݒ�
	
	LPDIRECT3DDEVICE9 d3d_device; //!< @brief DirectX�f�o�C�X���
	
	std::map<std::string, LPDIRECT3DTEXTURE9> texture_list; //!< @brief �e�N�X�`�����X�g
};

class DxManager : public Singleton<DxManager>
{
public:

	/**
	* @brief DirectX ��������
	* @param �E�B���h�E�n���h��
	* @return �������ɐ��������ꍇ => true
	*/
	bool InitDirectX(HWND windowHandle_);

	/**
	* @brief 2D��Ԃɕ`��(���W�ϊ��Ȃ�)
	*/
	void StartDraw2D();

	/**
	* @brief 3D��Ԃɕ`��(���W�ϊ�����)
	*/
	void StartDraw3D();

	/**
	* @brief DirectX�ł̕`��������
	*/
	void EndDraw();

	/**
	* @brief �t�H���g�̃f�o�C�X���쐬
	* @param �t�H���g�̑傫�����w��
	* @return �f�o�C�X�쐬�ɐ��� => true
	*/
	bool CreateFontDevice(t_Size size_);

	/**
	* @return DirectX �\���̂̃A�h���X��Ԃ�
	*/
	t_DxStatus* GetStatus() {
		if (!&m_dx_status) { return false; }
		return &m_dx_status;
	}

	/**
	* @return MatView �̃A�h���X��Ԃ�
	*/
	D3DXMATRIX* GetViewMatrix() {
		if (!&m_mat_view) { return false; }
		return &m_mat_view;
	}

	/**
	* @return m_Font �̃A�h���X��Ԃ�
	*/
	LPD3DXFONT& GetFont() {
		return m_font;
	}
protected:
	/**
	* @brief �J��������������
	*/
	void Transform();
	/**
	* @brief DirectX�ł̕`�����������
	*/
	void StartDraw();
	/**
	* @brief �����̐ݒ�
	*/
	void SetLighting();

protected:

	t_DxStatus m_dx_status;		//!< @brief DirectX �̎��ӏ���ۊ�

	D3DXMATRIX m_mat_proj, m_mat_view; //!< @brief ���_���s��

	LPD3DXFONT m_font;			//!< �t�H���g�̏��

	D3DXVECTOR3 m_camera_pos;		//!< �J�����ʒu
	D3DXVECTOR3 m_eye_pos;		//!< �����_
	D3DXVECTOR3 m_up_vector;		//!< �J�����̌���


private:
	friend Singleton<DxManager>;

	DxManager() :
		m_camera_pos(0.f, 0.f, -10.f),
		m_eye_pos(0.0f, 0.0f, 0.0f),
		m_up_vector(0.0f, 1.0f, 0.0f)
	{ 
		m_font = nullptr; 
	};
	virtual ~DxManager() {};

	DxManager(const DxManager&) = delete;
	DxManager& operator=(const DxManager&) = delete;
	DxManager(const DxManager&&) = delete;
	DxManager& operator=(const DxManager&&) = delete;
};



#endif