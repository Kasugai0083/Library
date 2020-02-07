#include "Drawer3D.h"
#include "XFile.h"
#include "HandMade.h"
#include "Grid.h"

/**
* XFile�֘A�̊֐�
*/

#pragma region ���W�ϊ��֐�


void TransNormal(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_) {
	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	D3DXMATRIX world_matrix, trans_matrix, view_matrix; 				//!< @brief ���W�n�̍s��

	D3DXMATRIX rot_matrix_x, rot_matrix_y, rot_matrix_z, rot_matrix; 	//!< @brief ��]�s��

	D3DXMATRIX scale_matrix; 											//!< @brief �g�k�s��

	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixIdentity(&rot_matrix);
	D3DXMatrixIdentity(&view_matrix);

	HandMade::Translation(&trans_matrix, pos_.x, pos_.y, pos_.z);
	HandMade::Scaling(&scale_matrix, scale_.x, scale_.y, scale_.z);

	HandMade::RotationX(&rot_matrix_x, D3DXToRadian(angle_.x));
	HandMade::RotationY(&rot_matrix_y, D3DXToRadian(angle_.y));
	HandMade::RotationZ(&rot_matrix_z, D3DXToRadian(angle_.z));

	rot_matrix *= rot_matrix_x * rot_matrix_y * rot_matrix_z;

	world_matrix = scale_matrix * trans_matrix * rot_matrix * view_matrix;

	mgr->GetStatus()->d3d_device->SetTransform(D3DTS_WORLD, &world_matrix);

}

void TransBillboard(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_) {

	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	D3DXMATRIX world_matrix, trans_matrix, view_matrix; 				//!< @brief ���W�n�̍s��

	D3DXMATRIX rot_matrix_x, rot_matrix_y, rot_matrix_z, rot_matrix; 	//!< @brief ��]�s��

	D3DXMATRIX scale_matrix; 											//!< @brief �g�k�s��

	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixIdentity(&rot_matrix);
	D3DXMatrixIdentity(&view_matrix);

	HandMade::Translation(&trans_matrix, pos_.x, pos_.y, pos_.z);
	HandMade::Scaling(&scale_matrix, scale_.x, scale_.y, scale_.z);

	HandMade::RotationX(&rot_matrix_x, D3DXToRadian(angle_.x));
	HandMade::RotationY(&rot_matrix_y, D3DXToRadian(angle_.y));
	HandMade::RotationZ(&rot_matrix_z, D3DXToRadian(angle_.z));

	rot_matrix *= rot_matrix_x * rot_matrix_y * rot_matrix_z;

	HandMade::BillBoard(&view_matrix, mgr->GetViewMatrix());

	world_matrix = scale_matrix * trans_matrix * rot_matrix * view_matrix;

	mgr->GetStatus()->d3d_device->SetTransform(D3DTS_WORLD, &world_matrix);
}

#pragma endregion

void Drawer3D::DrawXFile(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string fileName_)
{

	DxManager* mgr = DxManager::GetInstance();

	if (!mgr) { return; }

	TransNormal(pos_,scale_,angle_);


	if (m_ptr_xfile_list[fileName_]) { m_ptr_xfile_list[fileName_]->Draw(); }

}

void Drawer3D::DrawBillbord(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string fileName_)
{
	DxManager* mgr = DxManager::GetInstance();

	if (!mgr) { return; }

	TransBillboard(pos_, scale_, angle_);

	if (m_ptr_xfile_list[fileName_]) { m_ptr_xfile_list[fileName_]->Draw(); }

}

bool Drawer3D::LoadXFile(std::string fileName_) {
	m_ptr_xfile_list[fileName_] = new XFile;
	m_ptr_xfile_list[fileName_]->Load(fileName_);

	if (m_ptr_xfile_list[fileName_]) { return true; }
	
	return false;
}

/**
* �|���S���֘A�̕`��
*/


void Drawer3D::DrawSetting(float x_, float y_, float z_) {
	// DirectX �̃C���X�^���X��
	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	// ���[���h, �ړ�, �g�k�s���p��
	D3DXMATRIXA16 world_matrix, trans_matrix, scale_matrix, rot_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixIdentity(&rot_matrix);

	// �g�k
	// 1 / 100 �X�P�[���łȂ��Ƃł������ă��o�C�I
	HandMade::Scaling(&scale_matrix, 0.01f, 0.01f, 0.01f);

	// �ړ�
	D3DXMatrixTranslation(&trans_matrix, x_, y_, z_);

	// �r���{�[�h��
	HandMade::BillBoard(&world_matrix, mgr->GetViewMatrix());

	// �g�k�ƈړ��s��𔽉f
	world_matrix *= scale_matrix * rot_matrix * trans_matrix;
	mgr->GetStatus()->d3d_device->SetTransform(D3DTS_WORLD, &world_matrix);

	// ���C�e�B���O
	mgr->GetStatus()->d3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHW�Ŗ������_��LIGHT�������̂Ŗ����ɂ��Ă���

	// �J�����[�h(�̗���������`��)
	mgr->GetStatus()->d3d_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	mgr->GetStatus()->d3d_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);


}

void Drawer3D::DrawTexture(t_VertexPos v_, std::string fileName_)
{
	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	DrawSetting(v_.pos.x, v_.pos.y, v_.pos.z);

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;

	if (m_ptr_tex_list[fileName_] != nullptr) {
		left_tu = v_.tex_pos_start.x / m_ptr_tex_list[fileName_]->width;
		right_tu = (v_.tex_pos_start.x + v_.tex_pos_end.x) / m_ptr_tex_list[fileName_]->width;
		top_tv = v_.tex_pos_start.y / m_ptr_tex_list[fileName_]->height;
		bottom_tv = (v_.tex_pos_start.y + v_.tex_pos_end.y) / m_ptr_tex_list[fileName_]->height;
	}

	// �f�J�C�|���S�����
	// �����̒l������
	t_CustomVertex v[] =
	{
		{ D3DXVECTOR3(v_.tex_pos_start.x, v_.tex_pos_start.y + v_.tex_pos_end.y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },						// ����
		{ D3DXVECTOR3(v_.tex_pos_start.x + v_.tex_pos_end.x, v_.tex_pos_start.y + v_.tex_pos_end.y, 0.0f), D3DXVECTOR2(right_tu, top_tv) }, // �E��
		{ D3DXVECTOR3(v_.tex_pos_start.x + v_.tex_pos_end.x, v_.tex_pos_start.y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },					// �E��
		{ D3DXVECTOR3(v_.tex_pos_start.x, v_.tex_pos_start.y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },										// ����
	};

	if (m_ptr_tex_list[fileName_]) {
		mgr->GetStatus()->d3d_device->SetTexture(0, m_ptr_tex_list[fileName_]->texture_data);
	}

	mgr->GetStatus()->d3d_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(t_CustomVertex));
}

// �Ȑ��̕`�挻�ݒ�����
void Drawer3D::DrawLine(std::vector<t_LineDesc> descList_)
{
	// DirectX �̃C���X�^���X��
	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	DrawSetting(descList_[0].pos.x, descList_[0].pos.y, descList_[0].pos.z);

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

		// ������ Color �̒l����������
		// alpha �͑z��l
		DWORD color = D3DCOLOR_ARGB((int)(255 * descList_[i].alpha), 255, 255, 255);
		LineVertex new_vertex =
		{
			descList_[i].pos.x,
			descList_[i].pos.y,
			descList_[i].pos.z,
			1.0f,
			color
		};

		vertex_list.push_back(new_vertex);
	}

	mgr->GetStatus()->d3d_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, vertex_list.size() - 2, &vertex_list[0], sizeof(LineVertex));
}

bool Drawer3D::CreateTexture(std::string fileName_)
{
	t_Size size;
	D3DXIMAGE_INFO info;

	m_ptr_tex_list[fileName_] = new t_Texture;

	DxManager* mgr = DxManager::GetInstance();

	if (mgr == nullptr) { return false; }

	// 2�̗ݏ悶��Ȃ��P�[�X��z�肵�Č��̃T�C�Y���擾����D3DXCreateTextureFromFileEx�Ŏg��
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
		&m_ptr_tex_list[fileName_]->texture_data)))
	{
		return false;
	}
	else
	{
		// �e�N�X�`���T�C�Y�̎擾
		D3DSURFACE_DESC desc;

		if (FAILED(m_ptr_tex_list[fileName_]->texture_data->GetLevelDesc(0, &desc)))
		{
			m_ptr_tex_list[fileName_]->texture_data->Release();
			return false;
		}
		// �f�J���|���S�����
		// �����ł͑z����̒l�������Ă���
		m_ptr_tex_list[fileName_]->width = (float)desc.Width;
		m_ptr_tex_list[fileName_]->height = (float)desc.Height;
	}

	return true;
}

void Drawer3D::Release(std::string fileName_) {

	delete m_ptr_tex_list[fileName_];

	m_ptr_tex_list.clear();
}