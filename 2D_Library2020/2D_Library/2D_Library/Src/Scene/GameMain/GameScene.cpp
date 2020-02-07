#include "GameScene.h"


GameScene::~GameScene()
{
}


void GameScene::Init()
{
	// ƒV[ƒ“‘JˆÚ
	m_state = SceneState::UPDATE;
}

void GameScene::Update() {
	m_grid_drawer.UpdateLineManager();

	if (Device::KeyPress('A')) { m_state = SceneState::END; }
}

SceneID GameScene::End() {
	m_state = SceneState::INIT;
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
	m_drawer2d.DrawFont(font_pos, "‹Èü‚ğ•\¦");

	m_grid_drawer.DrawLine();

}

