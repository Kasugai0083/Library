#include "ResultScene.h"


ResultScene::~ResultScene()
{
}

void ResultScene::Init() {
	drawer.LoadTexture("Res/bomb.png");

	slider1.Load("Res/Slider01.png");
	slider2.Load("Res/Slider01.png");

	m_State = SceneState::UPDATE;
}

void ResultScene::Update() {

	slider1.Update();
	slider2.Update();

	if (Device::HasClickOnMouse()) { m_State = SceneState::END; }
}

SceneID ResultScene::End() {

	drawer.Release("Res/bomb.png");

	slider1.Release("Res/Slider01.png");
	slider2.Release("Res/Slider01.png");

	m_State = SceneState::INIT;
	return SceneID::TITLE;
}

SceneID ResultScene::Control() {
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
	return SceneID::RESULT;
}

void ResultScene::Draw() {
	{
		VertexPos v{ Pos3(-5.f,-5.f,0.f),Pos2(0.f,0.f),Pos2(256.f, 256.f) };
		drawer.DrawTexture(v, "Res/bomb.png");

		Vec2 font_pos(0.f, 0.f);
		drawer.DrawFont(font_pos, "2Dポリゴンを表示");

	}

	slider1.DrawSlider("Res/Slider01.png");
	slider2.DrawSlider("Res/Slider01.png");

}