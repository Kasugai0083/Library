#include "Slider.h"
#include "DirectX.h"
#include <math.h>
#include <Windows.h>
#include <string>

void Slider::UpdateNextSliderValue(bool plus_) {
	// �l���X�V����
	if (plus_) {
		m_slider_sta.next_value = m_slider_sta.max_value;
	}
	else {
		m_slider_sta.next_value = m_slider_sta.min_value;
	}

	// ���̒l�ƐV�����l�̍����o���āA���x���Z�o����
	float distance = fabsf(m_slider_sta.current_value - m_slider_sta.next_value);

	// �ړ��ɂ�����t���[����
	float moev_frame = 60.0f;
	m_slider_sta.move_speed = distance / moev_frame;
}

void Slider::UpdateSliderCurrentValue() {
	// next_value��current_value�ɍ��������move_speed�ŉ��Z����
	if (m_slider_sta.current_value <= m_slider_sta.next_value)
	{
		m_slider_sta.current_value = 
		min(m_slider_sta.current_value + m_slider_sta.move_speed, m_slider_sta.next_value);
	}
	else
	{
		m_slider_sta.current_value = 
		max(m_slider_sta.current_value - m_slider_sta.move_speed, m_slider_sta.next_value);
	}
}

void Slider::Update() {

	m_slider_sta.count++;
	UpdateSliderCurrentValue();

	if (m_slider_sta.count % 120 == 0)
	{
		UpdateNextSliderValue(true);
	}
	else if (m_slider_sta.count % 60 == 0)
	{
		UpdateNextSliderValue(false);
	}

}

void ReverseMove(float rate_, float size_, float& outPos_, float& outTexPos_, float& outSize_)
{
	// �䗦����`��J�n�ʒu�����炷
	outPos_ = 0.f;

	// �T�C�Y���䗦�ŕύX����
	outSize_ *= rate_;

	// �e�N�X�`���̍��W���䗦�̕��������炷
	outTexPos_ += (1.0f - rate_) * size_;
}

void Slider::DrawSlider(std::string fileName_, Dimendion dim_) {
	if (dim_ == Dimendion::DIMENSION_2) { DrawSlider2d(fileName_);}
	else if(dim_ == Dimendion::DIMENSION_3){ DrawSlider3d(fileName_); }
}

void Slider::DrawSlider2d(std::string fileName_)
{

	if (!m_drawer2d.GetTexture(fileName_)) { return; }
		
	float pos_x = m_slider_sta.x;
	float pos_y = m_slider_sta.y;
	float pos_z = 0.0f;
	float tex_x = 0.0f;
	float tex_y = 0.0f;
	float tex_width = m_drawer2d.GetTexture(fileName_)->width;
	float tex_height = m_drawer2d.GetTexture(fileName_)->height;

	// ����̒l��䗦�Ƃ��ĎZ�o����
	float rate = (m_slider_sta.current_value - m_slider_sta.min_value) 
				 / (m_slider_sta.max_value - m_slider_sta.min_value);

	if (m_slider_sta.dir == Direction::LEFT_TO_RIGHT) {
		tex_width *= rate;
	}
	else if (m_slider_sta.dir == Direction::RIGHT_TO_LEFT) {
		ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	}

	t_VertexPos a{ Pos3(pos_x, pos_y, pos_z), Pos2(tex_x,tex_y),Pos2(tex_width, tex_height) };

	m_drawer2d.DrawTexture(a, fileName_);

}

void Slider::DrawSlider3d(std::string fileName_)
{

	if (!m_drawer3d.GetTexture(fileName_)) { return; }
		
	float pos_x = m_slider_sta.x;
	float pos_y = m_slider_sta.y;
	float pos_z = m_slider_sta.z;
	float tex_x = 0.0f;
	float tex_y = 0.0f;
	float tex_width = m_drawer3d.GetTexture(fileName_)->width;
	float tex_height = m_drawer3d.GetTexture(fileName_)->height;

	// ����̒l��䗦�Ƃ��ĎZ�o����
	float rate = (m_slider_sta.current_value - m_slider_sta.min_value)
				 / (m_slider_sta.max_value - m_slider_sta.min_value);

	if (m_slider_sta.dir == Direction::LEFT_TO_RIGHT) {
		tex_width *= rate;
	}
	else if (m_slider_sta.dir == Direction::RIGHT_TO_LEFT) {
		ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	}

	t_VertexPos a{ Pos3(pos_x, pos_y, pos_z), Pos2(tex_x,tex_y),Pos2(tex_width, tex_height) };

	m_drawer3d.DrawTexture(a, fileName_);

}
