#include "Drawer3D.h"
#include "XFile.h"
#include "HandMade.h"
#include "Grid.h"

/**
* XFile関連の関数
*/

void Drawer3D::Trans(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_) {

	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixIdentity(&rot_matrix);
	D3DXMatrixIdentity(&view_matrix);

	HandMade::Translation(&trans_matrix, pos_.x, pos_.y, pos_.z);
	HandMade::Scaling(&scale_matrix, scale_.x, scale_.y, scale_.z);

	HandMade::RotationX(&rot_matrix_x, D3DXToRadian(angle_.x));
	HandMade::RotationY(&rot_matrix_y, D3DXToRadian(angle_.y));
	HandMade::RotationZ(&rot_matrix_z, D3DXToRadian(angle_.z));

	rot_matrix *= rot_matrix_x * rot_matrix_y * rot_matrix_z;

}

void Drawer3D::DrawXFile(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_)
{

	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (!Ins_DXManager) { return; }

	Trans(pos_,scale_,angle_);

	world_matrix = scale_matrix * trans_matrix * rot_matrix * view_matrix;

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if (m_pXFileList[name_]) { m_pXFileList[name_]->Draw(); }

}

void Drawer3D::DrawBillbord(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_)
{
	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (!Ins_DXManager) { return; }

	Trans(pos_, scale_, angle_);

	HandMade::BillBoard(&view_matrix, Ins_DXManager->GetViewMatrix());

	world_matrix = scale_matrix * trans_matrix * rot_matrix * view_matrix;

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if (m_pXFileList[name_]) { m_pXFileList[name_]->Draw(); }

}

bool Drawer3D::LoadXFile(std::string name_) {
	m_pXFileList[name_] = new XFile;
	m_pXFileList[name_]->Load(name_);

	if (m_pXFileList[name_]) { return true; }
	
	return false;
}

/**
* ポリゴン関連の描画
*/


void Drawer3D::DrawSetting(float x_, float y_, float z_) {
	// DirectX のインスタンス化
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	// ワールド, 移動, 拡縮行列を用意
	D3DXMATRIXA16 world, trans, scale, rot;
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&rot);

	// 拡縮
	// 1 / 100 スケールでないとでかすぎてヤバイ！
	HandMade::Scaling(&scale, 0.01f, 0.01f, 0.01f);

	// 移動
	D3DXMatrixTranslation(&trans, x_, y_, z_);

	// ビルボード化
	HandMade::BillBoard(&world, Ins_DXManager->GetViewMatrix());

	// 拡縮と移動行列を反映
	world *= scale * rot * trans;
	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world);

	// ライティング
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHWで無い頂点はLIGHTが効くので無効にしておく

	// カルモード(板の裏っかわも描画)
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Ins_DXManager->GetStatus()->m_D3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);


}

void Drawer3D::DrawTexture(VertexPos v_, std::string file_name_)
{
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	DrawSetting(v_.pos.X, v_.pos.Y, v_.pos.Z);

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;

	if (m_TextureList[file_name_] != nullptr) {
		left_tu = v_.tex_pos_start.X / m_TextureList[file_name_]->Width;
		right_tu = (v_.tex_pos_start.X + v_.tex_pos_end.X) / m_TextureList[file_name_]->Width;
		top_tv = v_.tex_pos_start.Y / m_TextureList[file_name_]->Height;
		bottom_tv = (v_.tex_pos_start.Y + v_.tex_pos_end.Y) / m_TextureList[file_name_]->Height;
	}

	// デカイポリゴン問題
	// ここの値も正常
	CustomVertex v[] =
	{
		{ D3DXVECTOR3(v_.tex_pos_start.X, v_.tex_pos_start.Y + v_.tex_pos_end.Y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },						// 左上
		{ D3DXVECTOR3(v_.tex_pos_start.X + v_.tex_pos_end.X, v_.tex_pos_start.Y + v_.tex_pos_end.Y, 0.0f), D3DXVECTOR2(right_tu, top_tv) }, // 右上
		{ D3DXVECTOR3(v_.tex_pos_start.X + v_.tex_pos_end.X, v_.tex_pos_start.Y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },					// 右下
		{ D3DXVECTOR3(v_.tex_pos_start.X, v_.tex_pos_start.Y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },										// 左下
	};

	if (m_TextureList[file_name_]) {
		Ins_DXManager->GetStatus()->m_D3DDevice->SetTexture(0, m_TextureList[file_name_]->TexutreData);
	}

	Ins_DXManager->GetStatus()->m_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

// 曲線の描画現在調整中
void Drawer3D::DrawLine(std::vector<LineDesc> desc_list)
{
	// DirectX のインスタンス化
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	DrawSetting(desc_list[0].m_Pos.X, desc_list[0].m_Pos.Y, desc_list[0].m_Pos.Z);

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

		// ここの Color の値がおかしい
		// m_Alpha は想定値
		DWORD color = D3DCOLOR_ARGB((int)(255 * desc_list[i].m_Alpha), 255, 255, 255);
		LineVertex new_vertex =
		{
			desc_list[i].m_Pos.X,
			desc_list[i].m_Pos.Y,
			desc_list[i].m_Pos.Z,
			1.0f,
			color
		};

		vertex_list.push_back(new_vertex);
	}

	Ins_DXManager->GetStatus()->m_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, vertex_list.size() - 2, &vertex_list[0], sizeof(LineVertex));
}

bool Drawer3D::CreateTexture(std::string file_name_)
{
	Size size;
	D3DXIMAGE_INFO info;

	m_TextureList[file_name_] = new Texture;

	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (Ins_DXManager == nullptr) { return false; }

	// 2の累乗じゃないケースを想定して元のサイズを取得してD3DXCreateTextureFromFileExで使う
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
		// テクスチャサイズの取得
		D3DSURFACE_DESC desc;

		if (FAILED(m_TextureList[file_name_]->TexutreData->GetLevelDesc(0, &desc)))
		{
			m_TextureList[file_name_]->TexutreData->Release();
			return false;
		}
		// デカいポリゴン問題
		// ここでは想定内の値が入っている
		m_TextureList[file_name_]->Width = (float)desc.Width;
		m_TextureList[file_name_]->Height = (float)desc.Height;
	}

	return true;
}

void Drawer3D::Release(std::string file_name_) {

	delete m_TextureList[file_name_];

	m_TextureList.clear();
}