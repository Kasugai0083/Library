#include "TitleScene.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init() {

	if (!m_drawer3d.LoadXFile("Res/Sample01.x")) {
		MessageBox(NULL, "XFileÇÃì«Ç›çûÇ›Ç…é∏îs", NULL, MB_OK);
	}

	m_state = SceneState::UPDATE;
}

void TitleScene::Update() {

	if (Device::HasClickOnMouse()) { m_state = SceneState::END; }
}

SceneID TitleScene::End() {
	m_drawer3d.ReleaseXFile();
	//	èIóπèàóù
	m_state = SceneState::INIT;
	return SceneID::GAME;
}

SceneID TitleScene::Control() {
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
	return SceneID::TITLE;
}

void TitleScene::Draw() {
	t_Vec2 font_pos(0.f, 0.f);
	m_drawer2d.DrawFont(font_pos, "XFileÇï\é¶");

	D3DXVECTOR3 pos(100.f, 100.f, 0.f);
	D3DXVECTOR3 scale(0.f, 0.f, 0.f);
	D3DXVECTOR3 angle(0.f, 0.f, 0.f);
	m_drawer3d.DrawXFile(pos, scale, angle, "Res/Sample01.x");
}