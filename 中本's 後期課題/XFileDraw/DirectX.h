#ifndef DIRECTX_H_
#define DIRECTX_H_

#include <d3d9.h>
#include <d3dx9.h>

// �ÓI���C�u����
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define MAX_TEXTURE_NUM (100)

/** @brief �t�H���g�J���[ */
enum FontColor
{
	Black,			//!< ��
	White,			//!< ��
	Red,			//!< ��
	Yellow,
};

// @brief �t�H���g�T�C�Y */
enum FontSize
{
	Small,			//!< ��
	Regular,		//!< ��
	Large,			//!< ��
	FontSizeMax,	//!< �T�C�Y�ő吔
};

#define SMALL_FONT_SIZE (16)	//!< �t�H���g�T�C�Y(��)
#define REGULAR_FONT_SIZE (24)	//!< �t�H���g�T�C�Y(��)
#define LARGE_FONT_SIZE (64)	//!< �t�H���g�T�C�Y(��)


extern LPDIRECT3DDEVICE9 g_pD3DDevice;

// �\���̐錾
typedef struct _VERTEX
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex_pos;
}VERTEX;

typedef struct
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	int m_Width;
	int m_Height;
} TEXTURE_DATA;
extern TEXTURE_DATA g_TextureList[MAX_TEXTURE_NUM];

// �f�o�C�X������
bool InitDirectX(HWND window_handle, HINSTANCE hInstans);
void Transform(void);

// �`��J�n
void StartDraw(void);

// �`��J�n
void EndDraw(void);

// ���C�e�B���O�̐ݒ�
void SetLighting(void);

// �O���t�B�N�X�f�o�C�X�̎擾
const LPDIRECT3DDEVICE9 GetD3DDevice(void);

// �e�N�X�`���ǂݍ���
int LoadTexture(const char* fileName_, int useId_ = -1);
bool IsUseTexture(int textureId_);
const TEXTURE_DATA* GetTextureData(int textureId_);

// �e�N�X�`�����
void ReleaseTexture(int textureId_);

// �`��֐�
void DrawUVMappingTexture(float x, float y, TEXTURE_DATA* texture_data, float texture_x, float texture_y, float rect_width, float rect_height);

TEXTURE_DATA* GetTexture(int texture_id);


bool CreateFontDevice();
void DrawFont(float pos_x, float pos_y, const char* text, FontSize size, FontColor color);

#endif