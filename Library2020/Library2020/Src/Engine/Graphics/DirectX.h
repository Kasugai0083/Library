#ifndef DIRECTX_H_
#define DIRECTX_H_

#include "../../Utility/SingletonTemplate.h"
#include "..//..//Utility/Size.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>

/**
* @brief 
* DirectX���������E�Ǘ�����N���X
*/

/**
* @brief DirextX�X�e�[�^�X�\����\n
* �󂯓n�����ȗ������邽�߂ɍ\���̂ɓZ�߂�
*/
struct DXStatus 
{
	LPDIRECT3D9 m_D3DInterface;	//!< @brief DirectX�C���^�[�t�F�[�X
	
	D3DPRESENT_PARAMETERS* m_pD3DPresentParam; //!< @brief DirectX�̐ݒ�
	
	LPDIRECT3DDEVICE9 m_D3DDevice; //!< @brief DirectX�f�o�C�X���
	
	std::map<std::string, LPDIRECT3DTEXTURE9> m_TextureList; //!< @brief �e�N�X�`�����X�g
};

class DXManager : public Singleton<DXManager>
{
public:

	/**
	* @brief DirectX ��������
	* @param �E�B���h�E�n���h��
	* @return �������ɐ��������ꍇ => true
	*/
	bool InitDirectX(HWND window_handle);


	void StartDraw2D();
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
	bool CreateFontDevice(Size size_);

	/**
	* @return DirectX �\���̂̃A�h���X��Ԃ�
	*/
	DXStatus* GetStatus() {
		if (!&m_DXStatus) { return false; }
		return &m_DXStatus;
	}

	/**
	* @return MatView �̃A�h���X��Ԃ�
	*/
	D3DXMATRIX* GetViewMatrix() {
		if (!&m_MatView) { return false; }
		return &m_MatView;
	}

	/**
	* @return m_Font �̃A�h���X��Ԃ�
	*/
	LPD3DXFONT& GetFont() {
		return m_Font;
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

	DXStatus m_DXStatus;		//!< @brief DirectX �̎��ӏ���ۊ�

	D3DXMATRIX m_MatProj, m_MatView; //!< @brief ���_���s��

	LPD3DXFONT m_Font;			//!< �t�H���g�̏��

	D3DXVECTOR3 camera_pos;		//!< �J�����ʒu
	D3DXVECTOR3 eye_pos;		//!< �����_
	D3DXVECTOR3 up_vector;		//!< �J�����̌���


private:
	friend Singleton<DXManager>;

	DXManager() :
		camera_pos(0.f, 0.f, -10.f),
		eye_pos(0.0f, 0.0f, 0.0f),
		up_vector(0.0f, 1.0f, 0.0f)
	{ 
		m_Font = nullptr; 
	};
	virtual ~DXManager() {};

	DXManager(const DXManager&) = delete;
	DXManager& operator=(const DXManager&) = delete;
	DXManager(const DXManager&&) = delete;
	DXManager& operator=(const DXManager&&) = delete;
};



#endif