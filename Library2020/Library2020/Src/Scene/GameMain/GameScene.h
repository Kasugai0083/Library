#pragma once
#include "../SceneBase.h"
#include "../../Engine/Graphics/Grid.h"


/**
* @brief
* ゲームメインのシーン処理
*/

//!< 曲線の通過点を指定
namespace {
	t_Vec3 start(-5.f, -1.f, 0.f);
	t_Vec3 center(10.f, 2.f, 0.f);
	t_Vec3 end(20.f, -2.f, 0.f);
}

class GameScene : public SceneBase
{
public:
	//!< コンストラクタ
	GameScene() : 
		m_grid_drawer(start, center, end)
	{}
	~GameScene()override;		//!< デストラクタ
private:
	void Init()override;		//!< シーンの初期化
	void Update()override;		//!< シーンの更新
	SceneID End()override;		//!< シーンの解放
	SceneID Control()override;	//!< シーンの制御
	void Draw()override;		//!< シーンの描画
private:
	Drawer2D m_drawer2d;			//!< フォント表示に使用
	Drawer3D m_drawer3d;			//!< フォント表示に使用
	LineDrawer m_grid_drawer;			//!< XFileの描画に使用
};

