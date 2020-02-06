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
* DirectXを初期化・管理するクラス
*/

/**
* Texture のデータとサイズを管理する構造体
*/
struct t_Texture {
	LPDIRECT3DTEXTURE9 texture_data;		//!< テクスチャデータ
	float width;						//!< 横幅
	float height;						//!< 縦幅
};

/**
* @brief ポリゴン描画に必要な頂点情報
* @param pos 座標
* @param tex_pos テクスチャ座標
*/
struct t_CustomVertex {

	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex_pos;

};

/**
* @brief ポリゴン描画に必要な頂点情報
* @param pos 座標
* @param tex_pos_start テクスチャ座標開始点
* @param tex_pos_end テクスチャ座標終了点
*/
struct t_VertexPos {

	Pos3 pos;
	Pos2 tex_pos_start, tex_pos_end;

};

/**
* @enum 各描画関数の描画次元をしていするのに使用
*/
enum class Dimendion {
	DIMENSION_2,
	DIMENSION_3,
};

/**
* @brief DirextXステータス構造体\n
* 受け渡しを簡略化するために構造体に纏める
*/
struct t_DxStatus 
{
	LPDIRECT3D9 d3d_interface;	//!< @brief DirectXインターフェース
	
	D3DPRESENT_PARAMETERS* d3d_present_param; //!< @brief DirectXの設定
	
	LPDIRECT3DDEVICE9 d3d_device; //!< @brief DirectXデバイス情報
	
	std::map<std::string, LPDIRECT3DTEXTURE9> texture_list; //!< @brief テクスチャリスト
};

class DxManager : public Singleton<DxManager>
{
public:

	/**
	* @brief DirectX を初期化
	* @param ウィンドウハンドル
	* @return 初期化に成功した場合 => true
	*/
	bool InitDirectX(HWND windowHandle_);

	/**
	* @brief 2D空間に描画(座標変換なし)
	*/
	void StartDraw2D();

	/**
	* @brief 3D空間に描画(座標変換あり)
	*/
	void StartDraw3D();

	/**
	* @brief DirectXでの描画情報を解放
	*/
	void EndDraw();

	/**
	* @brief フォントのデバイスを作成
	* @param フォントの大きさを指定
	* @return デバイス作成に成功 => true
	*/
	bool CreateFontDevice(t_Size size_);

	/**
	* @return DirectX 構造体のアドレスを返す
	*/
	t_DxStatus* GetStatus() {
		if (!&m_dx_status) { return false; }
		return &m_dx_status;
	}

	/**
	* @return MatView のアドレスを返す
	*/
	D3DXMATRIX* GetViewMatrix() {
		if (!&m_mat_view) { return false; }
		return &m_mat_view;
	}

	/**
	* @return m_Font のアドレスを返す
	*/
	LPD3DXFONT& GetFont() {
		return m_font;
	}
protected:
	/**
	* @brief カメラ情報を初期化
	*/
	void Transform();
	/**
	* @brief DirectXでの描画情報を初期化
	*/
	void StartDraw();
	/**
	* @brief 光源の設定
	*/
	void SetLighting();

protected:

	t_DxStatus m_dx_status;		//!< @brief DirectX の周辺情報を保管

	D3DXMATRIX m_mat_proj, m_mat_view; //!< @brief 視点情報行列

	LPD3DXFONT m_font;			//!< フォントの情報

	D3DXVECTOR3 m_camera_pos;		//!< カメラ位置
	D3DXVECTOR3 m_eye_pos;		//!< 注視点
	D3DXVECTOR3 m_up_vector;		//!< カメラの向き


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