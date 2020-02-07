#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Slider.h"

/**
* @brief
* リザルトシーンの処理
*/

namespace {
	Pos3 pos1(5.f, 5.f, 0.f);
	Pos3 pos2(0.f, 0.f, 10.f);
}

class ResultScene :public SceneBase
{
public:
	//!< コンストラクタ
	ResultScene() : 
		m_slider1(pos1, Direction::LEFT_TO_RIGHT),
		m_slider2(pos2, Direction::RIGHT_TO_LEFT)
	{}
	~ResultScene()override;		//!< デストラクタ
private:
	void Init()override;		//!< シーンの初期化
	void Update()override;		//!< シーンの更新
	SceneID End()override;		//!< シーンの解放
	SceneID Control()override;	//!< シーンの制御
	void Draw()override;		//!< シーンの描画
private:
	Drawer2D m_drawer2d;			//!< フォント表示に使用
	Drawer3D m_drawer3d;			//!< フォント表示に使用
	
	//!< スライダーの描画に使用
	Slider m_slider1;				
	Slider m_slider2;				 

};

