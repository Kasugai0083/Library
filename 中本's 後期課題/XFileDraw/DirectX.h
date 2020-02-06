#ifndef DIRECTX_H_
#define DIRECTX_H_

#include <d3d9.h>
#include <d3dx9.h>

// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define MAX_TEXTURE_NUM (100)

/** @brief フォントカラー */
enum FontColor
{
	Black,			//!< 黒
	White,			//!< 白
	Red,			//!< 赤
	Yellow,
};

// @brief フォントサイズ */
enum FontSize
{
	Small,			//!< 小
	Regular,		//!< 中
	Large,			//!< 大
	FontSizeMax,	//!< サイズ最大数
};

#define SMALL_FONT_SIZE (16)	//!< フォントサイズ(小)
#define REGULAR_FONT_SIZE (24)	//!< フォントサイズ(中)
#define LARGE_FONT_SIZE (64)	//!< フォントサイズ(大)


extern LPDIRECT3DDEVICE9 g_pD3DDevice;

// 構造体宣言
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

// デバイス初期化
bool InitDirectX(HWND window_handle, HINSTANCE hInstans);
void Transform(void);

// 描画開始
void StartDraw(void);

// 描画開始
void EndDraw(void);

// ライティングの設定
void SetLighting(void);

// グラフィクスデバイスの取得
const LPDIRECT3DDEVICE9 GetD3DDevice(void);

// テクスチャ読み込み
int LoadTexture(const char* fileName_, int useId_ = -1);
bool IsUseTexture(int textureId_);
const TEXTURE_DATA* GetTextureData(int textureId_);

// テクスチャ解放
void ReleaseTexture(int textureId_);

// 描画関数
void DrawUVMappingTexture(float x, float y, TEXTURE_DATA* texture_data, float texture_x, float texture_y, float rect_width, float rect_height);

TEXTURE_DATA* GetTexture(int texture_id);


bool CreateFontDevice();
void DrawFont(float pos_x, float pos_y, const char* text, FontSize size, FontColor color);

#endif