#include "Slider.h"
#include "DirectX.h"
#include <math.h>
#include <Windows.h>
#include <string>

void Slider::UpdateNextSliderValue(bool plus_) {
	// 値を更新する
	if (plus_) {
		m_slider_sta.next_value = m_slider_sta.max_value;
	}
	else {
		m_slider_sta.next_value = m_slider_sta.min_value;
	}

	// 今の値と新しい値の差を出して、速度を算出する
	float distance = fabsf(m_slider_sta.current_value - m_slider_sta.next_value);

	// 移動にかかるフレーム数
	float moev_frame = 60.0f;
	m_slider_sta.move_speed = distance / moev_frame;
}

void Slider::UpdateSliderCurrentValue() {
	// next_valueとcurrent_valueに差があればmove_speedで演算する
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
	// 比率から描画開始位置をずらす
	outPos_ = 0.f;

	// サイズも比率で変更する
	outSize_ *= rate_;

	// テクスチャの座標も比率の分だけずらす
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

	// 現状の値を比率として算出する
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

	// 現状の値を比率として算出する
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
