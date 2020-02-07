#include "ResultScene.h"


ResultScene::~ResultScene()
{
}

void ResultScene::Init() {
	m_drawer2d.LoadTexture("Res/bomb.png");

	m_slider1.Load("Res/Slider01.png");
	m_slider2.Load("Res/Slider01.png");

	m_state = SceneState::UPDATE;
}

void ResultScene::Update() {

	m_slider1.Update();
	m_slider2.Update();

	if (Device::KeyPress('A')) { m_state = SceneState::END; }
}

SceneID ResultScene::End() {

	m_drawer2d.Release("Res/bomb.png");

	m_slider1.Release("Res/Slider01.png");
	m_slider2.Release("Res/Slider01.png");

	m_state = SceneState::INIT;
	return SceneID::TITLE;
}

SceneID ResultScene::Control() {
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
	return SceneID::RESULT;
}

void ResultScene::Draw() {
	{
		t_VertexPos v{ Pos2(0.f,0.f),Pos2(0.f,0.f),Pos2(256.f, 256.f) };
		m_drawer2d.DrawTexture(v, "Res/bomb.png");

		t_Vec2 font_pos(50.f, 50.f);
		m_drawer2d.DrawFont(font_pos, "2Dƒ|ƒŠƒSƒ“‚ð•\Ž¦");

	}

	//m_slider1.DrawSlider("Res/Slider01.png");
	//m_slider2.DrawSlider("Res/Slider01.png");

}