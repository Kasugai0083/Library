#include "Slider.h"
#include "DirectX.h"
#include <math.h>
#include <Windows.h>
#include <string>

void Slider::UpdateNextSliderValue(bool plus_) {
	// �l���X�V����
	if (plus_) {
		NextValue = MaxValue;
	}
	else {
		NextValue = MinValue;
	}

	// ���̒l�ƐV�����l�̍����o���āA���x���Z�o����
	float distance = fabsf(CurrentValue - NextValue);

	// �ړ��ɂ�����t���[����
	float moev_frame = 60.0f;
	MoveSpeed = distance / moev_frame;
}

void Slider::UpdateSliderCurrentValue() {
	// NextValue��CurrentValue�ɍ�file_name_�������MoveSpeed�ŉ��Z����
	if (CurrentValue <= NextValue)
	{
		CurrentValue = min(CurrentValue + MoveSpeed, NextValue);
	}
	else
	{
		CurrentValue = max(CurrentValue - MoveSpeed, NextValue);
	}
}

void Slider::Update() {

	count++;
	UpdateSliderCurrentValue();

	if (count % 120 == 0)
	{
		UpdateNextSliderValue(true);
	}
	else if (count % 60 == 0)
	{
		UpdateNextSliderValue(false);
	}

}

void ReverseMove(float rate, float size, float& out_pos, float& out_tex_pos, float& out_size)
{
	// �䗦����`��J�n�ʒu�����炷
	out_pos = 0.f;

	// �T�C�Y���䗦�ŕύX����
	out_size *= rate;

	// �e�N�X�`���̍��W���䗦�̕��������炷
	out_tex_pos += (1.0f - rate) * size;
}

void Slider::DrawSlider(std::string file_name_)
{

	if (!InsDrawer.CreateTexture(file_name_)) {
		MessageBox(NULL, "�摜�̓ǂݍ��݂Ɏ��s2", NULL, MB_OK);
	}

	float pos_x = X;
	float pos_y = Y;
	float pos_z = Z;
	float tex_x = 0.0f;
	float tex_y = 0.0f;
	float tex_width = InsDrawer.GetTexture(file_name_)->Width;
	float tex_height = InsDrawer.GetTexture(file_name_)->Height;

	// ����̒l��䗦�Ƃ��ĎZ�o����
	float rate = (CurrentValue - MinValue) / (MaxValue - MinValue);

	if (Dir == Direction::LeftToRight) {
		tex_width *= rate;
	}
	else if (Dir == Direction::RightToLeft) {
		ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	}

	VertexPos a{ Pos3(pos_x, pos_y, pos_z), Pos2(tex_x,tex_y),Pos2(tex_width, tex_height) };

	InsDrawer.DrawTexture(a, file_name_);

}
