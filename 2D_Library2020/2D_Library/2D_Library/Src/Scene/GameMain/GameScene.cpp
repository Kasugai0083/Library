#include "GameScene.h"

GameScene::~GameScene()
{
}


void GameScene::Init()
{
	//!< 曲線の通過点を指定
	
	Vec3 start(-5.f, -1.f, 0.f);
	Vec3 center(10.f, 2.f, 0.f);
	Vec3 end(20.f, -2.f, 0.f);
	
	m_grid_drawer.Init(start, center, end);
	// シーン遷移
	m_state = SceneState::UPDATE;
}

void GameScene::Update() {
	m_grid_drawer.UpdateLineManager();

	if (Device::KeyPress('A')) { m_state = SceneState::END; }
}

SceneID GameScene::End() {
	m_state = SceneState::INIT;

	m_grid_drawer;

	return SceneID::RESULT;
}

SceneID GameScene::Control() {
	switch (m_state)
	{
	case SceneState::INIT:
		Init();
		break;
	case SceneState::UPDATE:
		Update();
		break;
	case SceneState::END:
		return End();
	}
	return SceneID::GAME;
}

void GameScene::Draw() {
	t_Vec2 font_pos(0.f, 0.f);
	m_drawer2d.DrawFont(font_pos, "曲線を表示");

	m_grid_drawer.DrawLine();

}

