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
* XFile を描画するクラス
*/


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
	void DrawXFile(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);

	/**
	* @brief XFile をビルボードを適用して描画する
	* @param pos_ オブジェクトの座標
	* @param scale_  オブジェクトの拡縮
	* @param angle_  オブジェクトの回転
	* @param name_  オブジェクトの名前
	*/
	void DrawBillbord(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);

	/**
	* @brief XFile を読み込む
	* @param name_ XFile の名前を指定
	*/
	bool LoadXFile(std::string name_);

	/**
	* @brief 読み込んだ XFile を解放
	*/
	void ReleaseXFile() {
		m_pXFileList.clear();
	}

public:		//!< ポリゴン関連メソッド

	/**
	* @brief テクスチャを貼り付けたポリゴンを描画する
	* @param v_ ポリゴンの頂点情報 と テクスチャの座標情報
	* @param file_name_ m_TextureList の要素
	*/
	void DrawTexture(VertexPos v_, std::string file_name_);

	/**
	* @brief m_TextureList にテクスチャ情報を入力\n
	* 読み込みに失敗した場合、エラーメッセージを返す
	* @param file_name_ 要素番号を指定
	*/
	void LoadTexture(std::string file_name_) {
		if (!CreateTexture(file_name_)) {
			std::string msg = " の読み込みに失敗";
			std::string pop_msg = file_name_ + msg;

			MessageBox(NULL, pop_msg.c_str(), NULL, MB_OK);
		}
	}

	/**
	* @brief 曲線の描画
	* @param 曲線の頂点情報
	*/
	void DrawLine(std::vector<LineDesc> desc_list);

	/**
	* @brief テクスチャ情報を取得
	* @return テクスチャ情報のポインタを返す
	*/
	Texture* GetTexture(std::string file_name_) { return m_TextureList[file_name_]; }


	/**
	* @brief 指定したテクスチャ領域を解放
	* @param 領域を指定
	*/
	void Release(std::string file_name_);



private:	//!< XFile関連メソッド

	/**
	* @brief Draw() の内で使用\n
	* 移動・拡縮・回転を関数を用いて計算する
	*/
	void Trans(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_);

private:	//!< ポリゴン関連メソッド

	/**
	* @brief m_TextureList にテクスチャ情報を入力
	* @param file_name_ 要素番号を指定
	*/
	bool CreateTexture(std::string file_name_);

	void DrawSetting(float x_, float y_, float z_); //!< @brief DirectXのデバイス や 行列情報の初期化

private:	//!< XFile関連メンバ変数

	D3DXVECTOR3 m_Pos, m_Scale, m_Angle; 								//!< @brief オブジェクト情報

	D3DXMATRIX world_matrix, trans_matrix, view_matrix; 				//!< @brief 座標系の行列

	D3DXMATRIX rot_matrix_x, rot_matrix_y, rot_matrix_z, rot_matrix; 	//!< @brief 回転行列

	D3DXMATRIX scale_matrix; 											//!< @brief 拡縮行列

	std::map<std::string, XFile*> m_pXFileList; 						//!< @brief 画像情報をリスト化

private:	//!< ポリゴン関連メンバ変数

	std::map<std::string, Texture*>m_TextureList; //!< @brief 画像情報を保管

};

