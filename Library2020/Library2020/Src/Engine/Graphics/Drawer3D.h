#pragma once

#include "DirectX.h"
#include "XFile.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>

/**
* @brief
* XFile を描画するクラス
*/

struct t_LineDesc;

class Drawer3D
{
public:		//!< XFile関連メソッド

	/**
	* @brief XFile を描画する
	* @param pos_ オブジェクトの座標 
	* @param scale_  オブジェクトの拡縮
	* @param angle_  オブジェクトの回転
	* @param name_  オブジェクトの名前
	*/
	void DrawXFile(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string fileName_);

	/**
	* @brief XFile をビルボードを適用して描画する
	* @param pos_ オブジェクトの座標
	* @param scale_  オブジェクトの拡縮
	* @param angle_  オブジェクトの回転
	* @param name_  オブジェクトの名前
	*/
	void DrawBillbord(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string fileName_);

	/**
	* @brief XFile を読み込む
	* @param name_ XFile の名前を指定
	*/
	bool LoadXFile(std::string fileName_);

	/**
	* @brief 読み込んだ XFile を解放
	*/
	void ReleaseXFile() {
		for (auto test : m_xfile_list) {
			if (test.second != nullptr) {
				delete test.second;
				test.second = nullptr;
			}
		}
	}

public:		//!< ポリゴン関連メソッド

	/**
	* @brief テクスチャを貼り付けたポリゴンを描画する
	* @param v_ ポリゴンの頂点情報 と テクスチャの座標情報
	* @param fileName_ m_ptr_tex_list の要素
	*/
	void DrawTexture(t_VertexPos v_, std::string fileName_);

	/**
	* @brief m_ptr_tex_list にテクスチャ情報を入力\n
	* 読み込みに失敗した場合、エラーメッセージを返す
	* @param fileName_ 要素番号を指定
	*/
	void LoadTexture(std::string fileName_) {
		if (!CreateTexture(fileName_)) {
			std::string msg = " の読み込みに失敗";
			std::string pop_msg = fileName_ + msg;

			MessageBox(NULL, pop_msg.c_str(), NULL, MB_OK);
		}
	}

	/**
	* @brief 曲線の描画
	* @param 曲線の頂点情報
	*/
	void DrawLine(std::vector<t_LineDesc> descList_);

	/**
	* @brief テクスチャ情報を取得
	* @return テクスチャ情報のポインタを返す
	*/
	t_Texture* GetTexture(std::string fileName_) { return m_ptr_tex_list[fileName_]; }


	/**
	* @brief 指定したテクスチャ領域を解放
	*/
	void Release();

private:	//!< ポリゴン関連メソッド

	/**
	* @brief m_ptr_tex_list にテクスチャ情報を入力
	* @param fileName_ 要素番号を指定
	*/
	bool CreateTexture(std::string fileName_);

	void DrawSetting(float x_, float y_, float z_); //!< @brief DirectXのデバイス や 行列情報の初期化

private:	//!< XFile関連メンバ変数

	std::map<std::string, XFile*> m_xfile_list; 						//!< @brief 画像情報をリスト化

private:	//!< ポリゴン関連メンバ変数

	std::map<std::string, t_Texture*> m_ptr_tex_list; //!< @brief 画像情報を保管

};

