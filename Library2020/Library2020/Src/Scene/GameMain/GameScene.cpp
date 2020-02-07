#include "GameScene.h"


GameScene::~GameScene()
{
}


void GameScene::Init()
{
	// ÉVÅ[ÉìëJà⁄
	m_state = SceneState::UPDATE;
}

void GameScene::Update() {
	m_grid_drawer.UpdateLineManager();

	if (Device::HasClickOnMouse()) { m_state = SceneState::END; }
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
	m_drawer2d.DrawFont(font_pos, "ã»ê¸Çï\é¶");

	m_grid_drawer.DrawLine(Dimendion::DIMENSION_3);

}

