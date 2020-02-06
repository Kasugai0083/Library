#include "DirectX.h"
#include "HandMade.h"
#include "..//Device.h"
#include <Windows.h>

void DXManager::StartDraw2D()
{
	StartDraw();
	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void DXManager::StartDraw3D()
{
	StartDraw();
	Transform();
	SetLighting();
}

bool DXManager::InitDirectX(HWND window_handle)
{
	// �C���^�[�t�F�[�X�쐬
	m_DXStatus.m_D3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_DXStatus.m_D3DInterface == NULL)
	{
		// �쐬���s
		return false;
	}
	
	m_DXStatus.m_pD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (m_DXStatus.m_pD3DPresentParam == NULL)
	{
		return false;
	}
	ZeroMemory(m_DXStatus.m_pD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	m_DXStatus.m_pD3DPresentParam->BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	m_DXStatus.m_pD3DPresentParam->BackBufferFormat = D3DFMT_UNKNOWN;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	m_DXStatus.m_pD3DPresentParam->Windowed = true;
	//���̉𑜓x
	m_DXStatus.m_pD3DPresentParam->BackBufferWidth = WIN_W;
	//�c�̉𑜓x
	m_DXStatus.m_pD3DPresentParam->BackBufferHeight = WIN_H;
	//�t���X�N���[���̃��t���b�V�����[�g
	m_DXStatus.m_pD3DPresentParam->FullScreen_RefreshRateInHz = 0.f;

	// �X���b�v�G�t�F�N�g�ݒ� => �f�B�X�v���C�h���C�o�ˑ�
	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	m_DXStatus.m_pD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDevice�̍쐬
	if (FAILED(m_DXStatus.m_D3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		m_DXStatus.m_pD3DPresentParam,
		&m_DXStatus.m_D3DDevice)))
	{
		return false;
	}

	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;
	// �r���[�|�[�g�̕�
	view_port.Width = m_DXStatus.m_pD3DPresentParam->BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = m_DXStatus.m_pD3DPresentParam->BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// �r���[�|�[�g�ݒ�
	if (FAILED(m_DXStatus.m_D3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void DXManager::Transform()
{
	
	// �L�[���͂ŃJ�����̈ړ� start
	if (Device::KeyOn(VK_RIGHT)) { eye_pos.x += 0.1f; }
	if (Device::KeyOn(VK_LEFT)) { eye_pos.x -= 0.1f; }
	if (Device::KeyOn(VK_UP)) { eye_pos.y += 0.1f; }
	if (Device::KeyOn(VK_DOWN)) { eye_pos.y -= 0.1f; }
	// �L�[���͂ŃJ�����̈ړ� end

	// �L�[���͂ŃJ�����̈ړ� start
	if (Device::KeyOn('D')) { camera_pos.x += 0.1f; eye_pos.x += 0.1f; }
	if (Device::KeyOn('A')) { camera_pos.x -= 0.1f; eye_pos.x -= 0.1f; }
	if (Device::KeyOn('W')) { camera_pos.y += 0.1f; eye_pos.y += 0.1f; }
	if (Device::KeyOn('S')) { camera_pos.y -= 0.1f; eye_pos.y -= 0.1f; }
	// �L�[���͂ŃJ�����̈ړ� end

	// �J�����̈ړ�
	//static float test = 1.f;

	//test++;

	//float rad = test * 3.14f / 180.f;
	//float distance = 10.0f;
	//D3DXVECTOR3 vec = D3DXVECTOR3(
	//	sinf(rad) * distance,
	//	0.0f,
	//	-cosf(rad) * distance
	//);

	//camera_pos.z += vec.z;
	//camera_pos.x += vec.x;
	//�J�����̈ړ� end

	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXMatrixIdentity(&m_MatView);
	D3DXMatrixLookAtLH(&m_MatView, 
		&camera_pos,				// �J�������W
		&eye_pos,					// �����_���W
		&up_vector);				// �J�����̏�̌����̃x�N�g��
	m_DXStatus.m_D3DDevice->SetTransform(D3DTS_VIEW, &m_MatView);
	//�r���[���W�ϊ��p�̍s��Z�o end

	//�ˉe���W�ϊ��p�̍s��Z�o start
	D3DVIEWPORT9 vp;
	m_DXStatus.m_D3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&m_MatProj,
		D3DXToRadian(60),	// ��p
		aspect,				// �A�X�y�N�g��
		0.1f,				// near
		10000.0f);			// far
	m_DXStatus.m_D3DDevice->SetTransform(D3DTS_PROJECTION, &m_MatProj);
	//�ˉe���W�ϊ��p�̍s��Z�o end
}

void DXManager::StartDraw() {
	m_DXStatus.m_D3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.0f,	// Z�o�b�t�@�̏����l
		0);		// �X�e���V���o�b�t�@�̏����l

	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_DXStatus.m_D3DDevice->BeginScene();
}

void DXManager::EndDraw() {

	m_DXStatus.m_D3DDevice->EndScene();

	m_DXStatus.m_D3DDevice->Present(NULL, NULL, NULL, NULL);
}

void DXManager::SetLighting() {
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, 0, 1);
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.f;
	light.Diffuse.g = 1.f;
	light.Diffuse.b = 1.f;

	D3DXVec3Normalize((D3DXVECTOR3*)& light.Direction, &vec_direction);
	light.Range = 200.f;
	m_DXStatus.m_D3DDevice->SetLight(0, &light);
	m_DXStatus.m_D3DDevice->LightEnable(0, true);
	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

bool DXManager::CreateFontDevice(Size size_) {

	if (FAILED(D3DXCreateFont(m_DXStatus.m_D3DDevice,
		(int)size_.Width,
		(int)size_.Height,
		FW_REGULAR,
		NULL,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_SCRIPT,
		TEXT("�l�r�@�o�S�V�b�N"),
		&m_Font)))
	{
		return false;
	}
	return true;
}