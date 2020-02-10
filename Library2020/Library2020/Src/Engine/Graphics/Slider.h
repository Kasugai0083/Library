#pragma once

#include "Drawer2D.h"
#include "Drawer3D.h"
#include <string>

/**
* @brief
* スライダーを管理・描画するクラス
*/

/**
* @enum 方向を決定する列挙子
*/
enum class Direction {
	LEFT_TO_RIGHT,
	RIGHT_TO_LEFT
};

/**
* @brief スライダーのステータス
*/
struct t_SilderState {
	int count;				//!< @brief 経過フレームを保存

	float x;				//!< @brief スライダー描画位置(X)
	float y;				//!< @brief スライダー描画位置(Y)
	float z;				//!< @brief スライダー描画位置(Z)

	float min_value;			//!< @brief 最小値
	float max_value;			//!< @brief 最大値

	float current_value;		//!< @brief 現在の値
	float next_value;		//!< @brief 次の値
	float move_speed;		//!< @brief 移動速度

	Direction dir;			//!< @brief 進行方向
};

class Slider {
public:
	
	/**
	* @brief コンストラクタ
	* @param x_ スライダーのX座標
	* @param y_ スライダーのY座標
	* @param z_ スライダーのZ座標
	* @param dir_ スライダーの方向
	*/
	Slider(Pos3 pos_,Direction dir_)
	{
		m_slider_sta.count = 0;
		m_slider_sta.x = pos_.x;
		m_slider_sta.y = pos_.y;
		m_slider_sta.z = pos_.z;
		m_slider_sta.min_value = 0.f;
		m_slider_sta.max_value = 100.f;
		m_slider_sta.current_value = 0.f;
		m_slider_sta.next_value = 100.f;
		m_slider_sta.move_speed = 0.f;
		m_slider_sta.dir = dir_;
	}

	/**
	* @brief Drawer2Dを用いて画像を読み込み
	*/
	void Load(std::string fileName_) {	m_drawer2d.LoadTexture(fileName_);}

	/**
	* @brief スライダーの更新\n
	* スライダーのステータスを参照して増減を決定する
	*/
	void Update();

	void DrawSlider(std::string fileName_, Dimendion dim_);

	void Release(std::string fileName_) {	m_drawer2d.Release(); }

private:
	/**
	* @brief 2D空間にスライダーを描画する
	*/
	void DrawSlider2d(std::string fileName_);
	/**
	* @brief 3D空間にスライダーを描画する
	*/
	void DrawSlider3d(std::string fileName_);

	/**
	* @brief Update() 内で使用される関数
	*/
	void UpdateNextSliderValue(bool plus_);
	void UpdateSliderCurrentValue();

private:
	t_SilderState m_slider_sta;

	Drawer2D m_drawer2d;		//!< @brief 描画用の関数を呼び出す
	Drawer3D m_drawer3d;		//!< @brief 描画用の関数を呼び出す

};

