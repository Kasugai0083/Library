#include "TitleScene.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init() {

	//if (!drawer3d.LoadXFile("Res/Sample01.x")) {
	//	MessageBox(NULL, "XFileÇÃì«Ç›çûÇ›Ç…é∏îs", NULL, MB_OK);
	//}

	m_State = SceneState::UPDATE;
}

void TitleScene::Update() {

	if (Device::HasClickOnMouse()) { m_State = SceneState::END; }
}

SceneID TitleScene::End() {
	//drawer3d.ReleaseXFile();
	//	èIóπèàóù
	m_State = SceneState::INIT;
	return SceneID::GAME;
}

SceneID TitleScene::Control() {
	switch (m_State)
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
	drawer2d.DrawFont(font_pos, "XFileÇï\é¶");

}