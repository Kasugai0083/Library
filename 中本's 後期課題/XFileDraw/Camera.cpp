#include "Camera.h"

#include "DirectX.h"
#include "Vec.h"
#include <iostream>

/*
	カメラに必要な情報
		・カメラの位置
		・注視点(カメラが見ている位置)

	
	カメラの更新タイミング
		ゲーム処理
			↓
		当たり判定
			↓
		カメラの更新
			↓
		カメラの当たり判定
			↓
		描画処理
		※カメラ処理は描画処理の前にすること！
*/
void CAMERA::Update()
{

	//ビュー座標変換用の行列算出 start
	D3DXVECTOR3 camera_pos(m_CameraPos.x, m_CameraPos.y, m_CameraPos.z); // カメラ位置
	D3DXVECTOR3 eye_pos(m_EyePos.x, m_EyePos.y, m_EyePos.z);// 注視点
	D3DXVECTOR3 up_vector(m_CameraUp.x, m_CameraUp.y, m_CameraUp.z);	// カメラの向き;


	D3DXMatrixLookAtLH(&m_MatView,
		&camera_pos,				// カメラ座標
		&eye_pos,					// 注視点座標
		&up_vector);				// カメラの上の向きのベクトル
	
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_MatView);
	//ビュー座標変換用の行列算出 end

	D3DXMATRIX matProj;
	D3DXMatrixIdentity(&matProj);

	//射影座標変換用の行列算出 start
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	// 視錐台の作成
	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// 画角
		aspect,				// アスペクト比
		1.1f,				// near
		2000.0f);			// far
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//射影座標変換用の行列算出 end
}


void CAMERA::Move()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixRotationYawPitchRoll(&mat, m_Yaw, m_Pitch, m_Roll);

	D3DXVECTOR3 forward;
	D3DXVec3TransformNormal(&forward, &forward, &mat);
	forward.y = 0;

#pragma region カメラの移動
	// 前
	if (GetKey(W_KEY)) {
		m_CameraPos.x += sinf(m_Pitch) * 2;
		m_CameraPos.z += cosf(m_Pitch) * 2;
	}
	// 後
	if (GetKey(S_KEY)) {
		m_CameraPos.x -= sinf(m_Pitch) * 2;
		m_CameraPos.z -= cosf(m_Pitch) * 2;
	}
	// 左
	if (GetKey(A_KEY)) {
		m_CameraPos.x -= cosf(m_Pitch) * 2;
		m_CameraPos.z += sinf(m_Pitch) * 2;
	}
	// 右
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