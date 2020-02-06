#pragma once

#include "..//..//Utility/Vec2.h"
#include "..//..//Utility/Vec3.h"
#include "..//..//Utility/Size.h"
#include "DirectX.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <map>
#include <vector>

/**
* @brief
* 2Dポリゴン用の画像を保存・描画するクラス
*/

struct LineDesc;

class Drawer2D
{
public:

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
	* @brief DrawTextA でテキストを表示\n
	* DrawTextA の都合上、Z軸は設定できない
	* @param pos_ テキストの座標
	* @param text_ テキストの内容
	*/
	void DrawFont(Vec2 pos_, std::string text_);

	/**
	* @brief 指定したテクスチャ領域を解放
	* @param 領域を指定
	*/
	void Release(std::string file_name_);

private:
	/**
	* @brief m_TextureList にテクスチャ情報を入力
	* @param file_name_ 要素番号を指定
	*/
	bool CreateTexture(std::string file_name_);

	void DrawSetting(float x_, float y_, float z_); //!< @brief DirectXのデバイス や 行列情報の初期化

private:

	std::map<std::string, Texture*>m_TextureList; //!< @brief 画像情報を保管

};