#pragma once

#include "DirectX.h"
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

/**
* @brief 
* XFile を管理するクラス
* !このクラスはゲームループでインスタンス化しません!
*/

class XFile
{
public:

	/**
	* @brief コンストラクタ\n
	* メンバ変数を初期化する
	*/
	XFile() :
		m_material_num(0),
		m_mesh(NULL),
		m_mesh_material_list(NULL),
		m_ptr_tex_list(NULL)
	{
	}

	/**
	* @brief デストラクタ\n
	* 保存した XFile 情報を破棄する
	*/
	~XFile();

	/**
	* @brief XFile を読み込む
	* @param XFile のパスを指定する\n
	* 読み込まれた XFile は m_pFileList に保存
	*/
	bool Load(std::string fileName_);

	/**
	* @brief 読み込まれた XFile 情報に基づいて描画\n
	* XFileDrawer クラスで呼び出される
	*/
	void Draw();

private:
	/**
	* @brief XFile を読み込んだ際にマテリアル情報を保管
	*/
	DWORD m_material_num;
	D3DMATERIAL9* m_mesh_material_list;

	/**
	* @brief XFile を読み込んだ際にメッシュ情報を保管
	*/
	LPD3DXMESH m_mesh;

	/**
	* @brief XFile を読み込んだ際にテクスチャ情報を保管
	*/
	LPDIRECT3DTEXTURE9* m_ptr_tex_list;
	std::map<std::string, LPDIRECT3DTEXTURE9> m_tex_list;
	std::map<int, std::string> m_tex_name_list;

	/**
	* @brief XFile の情報を保管 
	*/
	std::map<std::string, XFile*> m_xfile_list;

};

