#include "Drawer2D.h"
#include "DirectX.h"
#include "HandMade.h"
#include "Grid.h"
#include <vector>

void Drawer2D::DrawTexture(t_VertexPos v_, std::string fileName_)
{
	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;
	
	if (m_texture_list[fileName_] != nullptr) {
		left_tu = v_.tex_pos_start.x / m_texture_list[fileName_]->width;
		right_tu =(v_.tex_pos_start.x + v_.tex_pos_end.x) / m_texture_list[fileName_]->width;
		top_tv = v_.tex_pos_start.y / m_texture_list[fileName_]->height;
		bottom_tv = (v_.tex_pos_start.y + v_.tex_pos_end.y) / m_texture_list[fileName_]->height;
	}

	// デカイポリゴン問題
	// ここの値も正常
	t_CustomVertex v[] =
	{
		{ D3DXVECTOR3(v_.tex_pos_start.x, v_.tex_pos_start.y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },															// 左上
		{ D3DXVECTOR3(v_.tex_pos_start.x + v_.tex_pos_end.x, v_.tex_pos_start.y, 0.0f), D3DXVECTOR2(right_tu, top_tv) },										// 右上
		{ D3DXVECTOR3(v_.tex_pos_start.x + v_.tex_pos_end.x, v_.tex_pos_start.y + v_.tex_pos_end.y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },					// 右下
		{ D3DXVECTOR3(v_.tex_pos_start.x, v_.tex_pos_start.y + v_.tex_pos_end.y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },										// 左下
	};

	if (m_texture_list[fileName_]) {
		mgr->GetStatus()->d3d_device->SetTexture(0, m_texture_list[fileName_]->texture_data);
	}
	// ライティング
	mgr->GetStatus()->d3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHWで無い頂点はLIGHTが効くので無効にしておく

	mgr->GetStatus()->d3d_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	mgr->GetStatus()->d3d_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(t_CustomVertex));
}

// 曲線の描画現在調整中
void Drawer2D::DrawLine(std::vector<t_LineDesc> descList_)
{
	// DirectX のインスタンス化
	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	struct LineVertex
	{
		float x;
		float y;
		float z;

		float w;

		DWORD color;
	};

	std::vector<LineVertex> vertex_list;

	for (int i = 0; i < (int)descList_.size(); i++)
	{
		float tu = 0.0f;
		float tv = 0.0f;

		// ここの Color の値がおかしい
		// m_Alpha は想定値
		DWORD color = D3DCOLOR_ARGB((int)(255 * descList_[i].m_Alpha), 255, 255, 255);
		LineVertex new_vertex =
		{
			descList_[i].m_Pos.X,
			descList_[i].m_Pos.Y,
			0.f,
			1.0f,
			color
		};

		vertex_list.push_back(new_vertex);
	}
	mgr->GetStatus()->d3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHWで無い頂点はLIGHTが効くので無効にしておく

	mgr->GetStatus()->d3d_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	mgr->GetStatus()->d3d_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, vertex_list.size() - 2, &vertex_list[0], sizeof(LineVertex));
}

bool Drawer2D::CreateTexture(std::string fileName_)
{
	t_Size size;
	D3DXIMAGE_INFO info;

	m_texture_list[fileName_] = new t_Texture;

	DxManager* mgr = DxManager::GetInstance();

	if (mgr == nullptr) { return false; }

	// 2の累乗じゃないケースを想定して元のサイズを取得してD3DXCreateTextureFromFileExで使う
	D3DXGetImageInfoFromFileA(fileName_.c_str(), &info);

	if (FAILED(D3DXCreateTextureFromFileExA(mgr->GetStatus()->d3d_device,
		fileName_.c_str(),
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&m_texture_list[fileName_]->texture_data)))
	{
		return false;
	}
	else
	{
		// テクスチャサイズの取得
		D3DSURFACE_DESC desc;

		if (FAILED(m_texture_list[fileName_]->texture_data->GetLevelDesc(0, &desc)))
		{
			m_texture_list[fileName_]->texture_data->Release();
			return false;
		}
		// デカいポリゴン問題
		// ここでは想定内の値が入っている
		m_texture_list[fileName_]->width = (float)desc.Width;
		m_texture_list[fileName_]->height = (float)desc.Height;
	}

	return true;
}

void Drawer2D::DrawFont(t_Vec2 pos_,std::string text_) {

	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	RECT rect =
	{
		(LONG)pos_.x,
		(LONG)pos_.y,
		(LONG)pos_.x + (LONG)1024.f,
		(LONG)pos_.y + (LONG)1024.f
	};

	LPD3DXFONT font = mgr->GetFont();

	font->DrawTextA(
		NULL,
		text_.c_str(),
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(255,255,255)
	);
}

void Drawer2D::Release(std::string fileName_) {

	delete[] m_texture_list[fileName_];

	m_texture_list.clear();
}