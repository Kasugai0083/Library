#ifndef CAMERA_H_
#define CAMERA_H_

#include "DirectX.h"
#include "Input.h"

class CAMERA
{
public:
	CAMERA(float camera_x, float camera_y, float camera_z)
	{
		m_CameraPos.x = camera_x;
		m_CameraPos.y = camera_y;
		m_CameraPos.z = camera_z;

		m_EyePos.x = 0.0f;
		m_EyePos.y = 5.0f;
		m_EyePos.z = -.0f;

		m_CameraUp.x = 0.0f;
		m_CameraUp.y = 1.0f;
		m_CameraUp.z = 0.0f;

		m_Move.x = 0.0f;
		m_Move.y = 0.0f;
		m_Move.z = 0.0f;

		m_RotateSpeed = 0.05f;

		m_Yaw   = 0.0f;
		m_Pitch = 0.0f;
		m_Roll  = 0.0f;

		D3DXMatrixIdentity(&m_MatView);
	}
	
	// �J�������W�̍X�V
	void Update();

	// �J�����̈ړ�
	void Move();

	// �}�E�X�ɂ��J������]
	void MouseRotate();
	
	// �J������View���Q�b�g�֐�
	D3DXMATRIX* GetView();

private:
	/* �J�����̈ʒu */
	D3DXVECTOR3 m_CameraPos;

	/* �����_ */
	D3DXVECTOR3 m_EyePos;

	/* �J�����̏�����̃x�N�g�� */
	D3DXVECTOR3 m_CameraUp;
	
	/* �J�����̈ړ��� */
	D3DXVECTOR3 m_Move;

	/* �J�����̃r���[����ۑ�����ϐ� */
	D3DXMATRIX m_MatView;

	/* �p�x */
	float m_Rad;

	/* ��]���x */
	float m_RotateSpeed;

	/* X����] */
	float m_Yaw;

	/* Y����] */
	float m_Pitch;

	/* Z����] */
	float m_Roll;

};


#endif