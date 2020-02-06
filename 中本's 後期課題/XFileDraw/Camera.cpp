#include "Camera.h"

#include "DirectX.h"
#include "Vec.h"
#include <iostream>

/*
	�J�����ɕK�v�ȏ��
		�E�J�����̈ʒu
		�E�����_(�J���������Ă���ʒu)

	
	�J�����̍X�V�^�C�~���O
		�Q�[������
			��
		�����蔻��
			��
		�J�����̍X�V
			��
		�J�����̓����蔻��
			��
		�`�揈��
		���J���������͕`�揈���̑O�ɂ��邱�ƁI
*/
void CAMERA::Update()
{

	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXVECTOR3 camera_pos(m_CameraPos.x, m_CameraPos.y, m_CameraPos.z); // �J�����ʒu
	D3DXVECTOR3 eye_pos(m_EyePos.x, m_EyePos.y, m_EyePos.z);// �����_
	D3DXVECTOR3 up_vector(m_CameraUp.x, m_CameraUp.y, m_CameraUp.z);	// �J�����̌���;


	D3DXMatrixLookAtLH(&m_MatView,
		&camera_pos,				// �J�������W
		&eye_pos,					// �����_���W
		&up_vector);				// �J�����̏�̌����̃x�N�g��
	
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_MatView);
	//�r���[���W�ϊ��p�̍s��Z�o end

	D3DXMATRIX matProj;
	D3DXMatrixIdentity(&matProj);

	//�ˉe���W�ϊ��p�̍s��Z�o start
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	// ������̍쐬
	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// ��p
		aspect,				// �A�X�y�N�g��
		1.1f,				// near
		2000.0f);			// far
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//�ˉe���W�ϊ��p�̍s��Z�o end
}


void CAMERA::Move()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixRotationYawPitchRoll(&mat, m_Yaw, m_Pitch, m_Roll);

	D3DXVECTOR3 forward;
	D3DXVec3TransformNormal(&forward, &forward, &mat);
	forward.y = 0;

#pragma region �J�����̈ړ�
	// �O
	if (GetKey(W_KEY)) {
		m_CameraPos.x += sinf(m_Pitch) * 2;
		m_CameraPos.z += cosf(m_Pitch) * 2;
	}
	// ��
	if (GetKey(S_KEY)) {
		m_CameraPos.x -= sinf(m_Pitch) * 2;
		m_CameraPos.z -= cosf(m_Pitch) * 2;
	}
	// ��
	if (GetKey(A_KEY)) {
		m_CameraPos.x -= cosf(m_Pitch) * 2;
		m_CameraPos.z += sinf(m_Pitch) * 2;
	}
	// �E
	if (GetKey(D_KEY)) {
		m_CameraPos.x += cosf(m_Pitch) * 2;
		m_CameraPos.z -= sinf(m_Pitch) * 2;
	}
#pragma endregion

	if (GetKey(SPACE_KEY)) { m_CameraPos.y += 3; }
	if (GetKey(L_CONTROL)) { m_CameraPos.y -= 3; }
}

void CAMERA::MouseRotate()
{
	SetCursorPos(960, 540);

	m_Yaw -= (GetMousePos().X - 960) / 1920 * 50;
	m_Pitch -= (GetMousePos().Y - 540) / 1080 * 20;
	if (m_Pitch > 90.0f) { m_Pitch = 180.0f - m_Pitch; }
	if (m_Pitch < -90.0f) { m_Pitch = -180.0f - m_Pitch; }

	m_EyePos.x = m_CameraPos.x + cosf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
	m_EyePos.y = m_CameraPos.y + sinf(D3DXToRadian(m_Pitch));
	m_EyePos.z = m_CameraPos.z + sinf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));

	if (GetKey(LEFT_KEY)) { m_Yaw += 5.0f; }
	if (GetKey(RIGHT_KEY)) { m_Yaw -= 5.0f; }
	if (GetKey(UP_KEY)) { m_Pitch += 5.0f; }
	if (GetKey(DOWN_KEY)) { m_Pitch -= 5.0f; }
}

D3DXMATRIX* CAMERA::GetView()
{
	return &m_MatView;
}