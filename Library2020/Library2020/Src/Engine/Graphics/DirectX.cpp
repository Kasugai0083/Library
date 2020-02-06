#include "DirectX.h"
#include "HandMade.h"
#include "..//Device.h"
#include <Windows.h>

void DxManager::StartDraw2D()
{
	StartDraw();
	m_dx_status.d3d_device->SetRenderState(D3DRS_LIGHTING, false);
}

void DxManager::StartDraw3D()
{
	StartDraw();
	Transform();
	SetLighting();
}

bool DxManager::InitDirectX(HWND windowHandle_)
{
	// �C���^�[�t�F�[�X�쐬
	m_dx_status.d3d_interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_dx_status.d3d_interface == NULL)
	{
		// �쐬���s
		return false;
	}
	
	m_dx_status.d3d_present_param = new D3DPRESENT_PARAMETERS;
	if (m_dx_status.d3d_present_param == NULL)
	{
		return false;
	}
	ZeroMemory(m_dx_status.d3d_present_param, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	m_dx_status.d3d_present_param->BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	m_dx_status.d3d_present_param->BackBufferFormat = D3DFMT_UNKNOWN;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	m_dx_status.d3d_present_param->Windowed = true;
	//���̉𑜓x
	m_dx_status.d3d_present_param->BackBufferWidth = WIN_W;
	//�c�̉𑜓x
	m_dx_status.d3d_present_param->BackBufferHeight = WIN_H;
	//�t���X�N���[���̃��t���b�V�����[�g
	m_dx_status.d3d_present_param->FullScreen_RefreshRateInHz = 0;

	// �X���b�v�G�t�F�N�g�ݒ� => �f�B�X�v���C�h���C�o�ˑ�
	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	m_dx_status.d3d_present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDevice�̍쐬
	if (FAILED(m_dx_status.d3d_interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandle_,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		m_dx_status.d3d_present_param,
		&m_dx_status.d3d_device)))
	{
		return false;
	}

	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;
	// �r���[�|�[�g�̕�
	view_port.Width = m_dx_status.d3d_present_param->BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = m_dx_status.d3d_present_param->BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// �r���[�|�[�g�ݒ�
	if (FAILED(m_dx_status.d3d_device->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void DxManager::Transform()
{
	
	// �L�[���͂ŃJ�����̈ړ� start
	if (Device::KeyOn(VK_RIGHT)) { m_eye_pos.x += 0.1f; }
	if (Device::KeyOn(VK_LEFT)) { m_eye_pos.x -= 0.1f; }
	if (Device::KeyOn(VK_UP)) { m_eye_pos.y += 0.1f; }
	if (Device::KeyOn(VK_DOWN)) { m_eye_pos.y -= 0.1f; }
	// �L�[���͂ŃJ�����̈ړ� end

	// �L�[���͂ŃJ�����̈ړ� start
	if (Device::KeyOn('D')) { m_camera_pos.x += 0.1f; m_eye_pos.x += 0.1f; }
	if (Device::KeyOn('A')) { m_camera_pos.x -= 0.1f; m_eye_pos.x -= 0.1f; }
	if (Device::KeyOn('W')) { m_camera_pos.y += 0.1f; m_eye_pos.y += 0.1f; }
	if (Device::KeyOn('S')) { m_camera_pos.y -= 0.1f; m_eye_pos.y -= 0.1f; }
	// �L�[���͂ŃJ�����̈ړ� end

	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXMatrixIdentity(&m_mat_view);
	D3DXMatrixLookAtLH(&m_mat_view, 
		&m_camera_pos,				// �J�������W
		&m_eye_pos,					// �����_���W
		&m_up_vector);				// �J�����̏�̌����̃x�N�g��
	m_dx_status.d3d_device->SetTransform(D3DTS_VIEW, &m_mat_view);
	//�r���[���W�ϊ��p�̍s��Z�o end

	//�ˉe���W�ϊ��p�̍s��Z�o start
	D3DVIEWPORT9 vp;
	m_dx_status.d3d_device->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&m_mat_proj,
		D3DXToRadian(60),	// ��p
		aspect,				// �A�X�y�N�g��
		0.1f,				// near
		10000.0f);			// far
	m_dx_status.d3d_device->SetTransform(D3DTS_PROJECTION, &m_mat_proj);
	//�ˉe���W�ϊ��p�̍s��Z�o end
}

void DxManager::StartDraw() {
	m_dx_status.d3d_device->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.0f,	// Z�o�b�t�@�̏����l
		0);		// �X�e���V���o�b�t�@�̏����l

	m_dx_status.d3d_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_dx_status.d3d_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_dx_status.d3d_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_dx_status.d3d_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_dx_status.d3d_device->BeginScene();
}

void DxManager::EndDraw() {

	m_dx_status.d3d_device->EndScene();

	m_dx_status.d3d_device->Present(NULL, NULL, NULL, NULL);
}

void DxManager::SetLighting() {
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, 0, 1);
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.f;
	light.Diffuse.g = 1.f;
	light.Diffuse.b = 1.f;

	D3DXVec3Normalize((D3DXVECTOR3*)& light.Direction, &vec_direction);
	light.Range = 200.f;
	m_dx_status.d3d_device->SetLight(0, &light);
	m_dx_status.d3d_device->LightEnable(0, true);
	m_dx_status.d3d_device->SetRenderState(D3DRS_LIGHTING, true);
}

bool DxManager::CreateFontDevice(t_Size size_) {

	if (FAILED(D3DXCreateFont(m_dx_status.d3d_device,
		(int)size_.width,
		(int)size_.height,
		FW_REGULAR,
		NULL,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_SCRIPT,
		TEXT("�l�r�@�o�S�V�b�N"),
		&m_font)))
	{
		return false;
	}
	return true;
}