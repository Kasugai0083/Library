#include "TitleScene.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init() {

	if (!Object.LoadXFile("Res/Sample01.x")) {
		MessageBox(NULL, "XFileÇÃì«Ç›çûÇ›Ç…é∏îs", NULL, MB_OK);
	}

	m_State = SceneState::UPDATE;
}

void TitleScene::Update() {

	if (Device::HasClickOnMouse()) { m_State = SceneState::END; }
}

SceneID TitleScene::End() {
	Object.ReleaseXFile();
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
	Vec2 font_pos(0.f, 0.f);
	drawer.DrawFont(font_pos, "XFileÇï\é¶");

	// XFileÇÃï`âÊ(ê≥ñ )
	Object.DrawXFile(
		D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(1.f, 1.f, 1.f),
		D3DXVECTOR3(20.f, 20.f, 20.f),
		"Res/Sample01.x"
	);


	// XFileÇÃï`âÊ(âEè„)
	Object.DrawBillbord(
		D3DXVECTOR3(5.f, 5.f, 0.f),
		D3DXVECTOR3(1.f, 1.f, 1.f),
		D3DXVECTOR3(20.f, 20.f, 20.f),
		"Res/Sample01.x"
	);

}