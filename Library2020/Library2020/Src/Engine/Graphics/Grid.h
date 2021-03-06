#pragma once

#include "../../Utility/Vec3.h"
#include "Drawer2D.h"
#include <d3dx9.h>
#include <vector>
#include "Drawer3D.h"

/*
	・曲線の描画
	以下の流れを参考に曲線の描画をする
	�@．あるオブジェクトの座標を一定フレーム毎に保存する
	�A．保存されてる座標と次の座標でベクトルを算出する
	�B．�Aのベクトルに対して直角なベクトルを算出する
	�C．�Bのベクトルを単位ベクトルにする
	�D．線の幅 / 2 を�Cのベクトルに掛ける
	�E．�Dのベクトルに座標を足した新しい座標を作る

	�F．�Dのベクトルを180度回転する
	�G．�Fのベクトルと座標を足した新しい座標を作る

	�H．�A〜�Gを繰り返してTriangleStripで描画するための頂点の塊を作る
*/

/**
* @brief 
* 曲線の情報を管理
*/

/**
* 線の座標と経過フレームを保存
*/
struct t_Line
{
	t_Vec3 pos;
	int counter;
};

/**
* @brief 線のステータスを管理
* @param width	線の幅
* @param start	線の開始点
* @param end		線の終点？
* @param center	線の中間点？
* @param timer	経過フレームを保存
* @param line		位置情報とタイマー
*/
struct t_LineManager 
{
	float width;				
	t_Vec3 start;				
	t_Vec3 end;					
	t_Vec3 center;				
	int timer;				
	std::vector<t_Line> line;	
};

/**
* @brief 線の位置情報と色彩濃度を保存
*/
struct t_LineDesc 
{
	t_Vec3 pos;
	float alpha;
};

class Drawer3D;

class LineDrawer {
public:

	/**
	* @brief コンストラクタ
	* @param start	線の開始点
	* @param center 線の中間点
	* @param end	線の終点
	*/
	LineDrawer(t_Vec3 start_, t_Vec3 center_,t_Vec3 end_)
	{
		// 10.f でしか描画されない
		// 訂正：Widthを上げるとどんどん高い位置で描画される
		// 原因を探る
		// �Dで Width の値の半分を乗算しているため、位置ずれが起きていると思われる
		m_line_mgr.width = 20.0f;
		m_line_mgr.line.clear();
		m_line_mgr.start = start_;
		m_line_mgr.end = end_;
		m_line_mgr.center = center_;
		m_line_mgr.timer = 0;

		t_Line line =
		{
			m_line_mgr.start,
			120,
		};
		m_line_mgr.line.push_back(line);
	}

	/**
	* @brief ６フレーム毎に次の線情報を作成する
	*/
	void UpdateLineManager();

	/**
	* @brief 曲線の描画
	*/
	void DrawLine(Dimendion dim_);

private:
	void UpdateLine(); 	//!< @brief counter を減算する

private:
	t_LineManager m_line_mgr;	//!< @brief 曲線の情報を管理

	Drawer2D m_drawer2d;			//!< @brief 描画関数を呼び出すために使用
	Drawer3D m_drawer3d;			//!< @brief 描画関数を呼び出すために使用

};