#include "Drawer2D.h"
#include "DirectX.h"
#include "HandMade.h"
#include "Grid.h"
#include <vector>

void Drawer2D::DrawTexture(VertexPos v_, std::string file_name_)
{
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;
	
	if (m_TextureList[file_name_] != nullptr) {
		left_tu = v_.tex_pos_start.X / m_TextureList[file_name_]->Width;
		right_tu =(v_.tex_pos_start.X + v_.tex_pos_end.X) / m_TextureList[file_name_]->Width;
		top_tv = v_.tex_pos_start.Y / m_TextureList[file_name_]->Height;
		bottom_tv = (v_.tex_pos_start.Y + v_.tex_pos_end.Y) / m_TextureList[file_name_]->Height;
	}

	// �f�J�C�|���S�����
	// �����̒l������
	CustomVertex v[] =
	{
		{ D3DXVECTOR3(v_.tex_pos_start.X, v_.tex_pos_start.Y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },															// ����
		{ D3DXVECTOR3(v_.tex_pos_start.X + v_.tex_pos_end.X, v_.tex_pos_start.Y, 0.0f), D3DXVECTOR2(right_tu, top_tv) },										// �E��
		{ D3DXVECTOR3(v_.tex_pos_start.X + v_.tex_pos_end.X, v_.tex_pos_start.Y + v_.tex_pos_end.Y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },					// �E��
		{ D3DXVECTOR3(v_.tex_pos_start.X, v_.tex_pos_start.Y + v_.tex_pos_end.Y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },										// ����
	};

	if (m_TextureList[file_name_]) {
		Ins_DXManager->GetStatus()->m_D3DDevice->SetTexture(0, m_TextureList[file_name_]->TexutreData);
	}
	// ���C�e�B���O
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHW�Ŗ������_��LIGHT�������̂Ŗ����ɂ��Ă���

	Ins_DXManager->GetStatus()->m_D3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	Ins_DXManager->GetStatus()->m_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

// �Ȑ��̕`�挻�ݒ�����
void Drawer2D::DrawLine(std::vector<LineDesc> desc_list)
{
	// DirectX �̃C���X�^���X��
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	struct LineVertex
	{
		float x;
		float y;
		float z;

		float w;

		DWORD color;
	};

	std::vector<LineVertex> vertex_list;

	for (int i = 0; i < (int)desc_list.size(); i++)
	{
		float tu = 0.0f;
		float tv = 0.0f;

		// ������ Color �̒l����������
		// m_Alpha �͑z��l
		DWORD color = D3DCOLOR_ARGB((int)(255 * desc_list[i].m_Alpha), 255, 255, 255);
		LineVertex new_vertex =
		{
			desc_list[i].m_Pos.X,
			desc_list[i].m_Pos.Y,
			0.f,
			1.0f,
			color
		};

		vertex_list.push_back(new_vertex);
	}
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHW�Ŗ������_��LIGHT�������̂Ŗ����ɂ��Ă���

	Ins_DXManager->GetStatus()->m_D3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	Ins_DXManager->GetStatus()->m_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, vertex_list.size() - 2, &vertex_list[0], sizeof(LineVertex));
}

bool Drawer2D::CreateTexture(std::string file_name_)
{
	Size size;
	D3DXIMAGE_INFO info;

	m_TextureList[file_name_] = new Texture;

	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (Ins_DXManager == nullptr) { return false; }

	// 2�̗ݏ悶��Ȃ��P�[�X��z�肵�Č��̃T�C�Y���擾����D3DXCreateTextureFromFileEx�Ŏg��
	D3DXGetImageInfoFromFileA(file_name_.c_str(), &info);

	if (FAILED(D3DXCreateTextureFromFileExA(Ins_DXManager->GetStatus()->m_D3DDevice,
		file_name_.c_str(),
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
		&m_TextureList[file_name_]->TexutreData)))
	{
		return false;
	}
	else
	{
		// �e�N�X�`���T�C�Y�̎擾
		D3DSURFACE_DESC desc;

		if (FAILED(m_TextureList[file_name_]->TexutreData->GetLevelDesc(0, &desc)))
		{
			m_TextureList[file_name_]->TexutreData->Release();
			return false;
		}
		// �f�J���|���S�����
		// �����ł͑z����̒l�������Ă���
		m_TextureList[file_name_]->Width = (float)desc.Width;
		m_TextureList[file_name_]->Height = (float)desc.Height;
	}

	return true;
}

void Drawer2D::DrawFont(Vec2 pos_,std::string text_) {

	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (Ins_DXManager == nullptr) { return; }

	RECT rect =
	{
		(LONG)pos_.X,
		(LONG)pos_.Y,
		(LONG)pos_.X + (LONG)1024.f,
		(LONG)pos_.Y + (LONG)1024.f
	};

	LPD3DXFONT font = Ins_DXManager->GetFont();

	font->DrawTextA(
		NULL,
		text_.c_str(),
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(255,255,255)
	);
}

void Drawer2D::Release(std::string file_name_) {

	delete[] m_TextureList[file_name_];

	m_TextureList.clear();
}