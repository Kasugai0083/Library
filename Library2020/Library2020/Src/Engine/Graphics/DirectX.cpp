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
	// インターフェース作成
	m_dx_status.d3d_interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_dx_status.d3d_interface == NULL)
	{
		// 作成失敗
		return false;
	}
	
	m_dx_status.d3d_present_param = new D3DPRESENT_PARAMETERS;
	if (m_dx_status.d3d_present_param == NULL)
	{
		return false;
	}
	ZeroMemory(m_dx_status.d3d_present_param, sizeof(D3DPRESENT_PARAMETERS));

	// バックバッファの数 => 1
	m_dx_status.d3d_present_param->BackBufferCount = 1;
	// バックバッファのフォーマット => D3DFMT_UNKNOWN(フォーマットを知りません)
	m_dx_status.d3d_present_param->BackBufferFormat = D3DFMT_UNKNOWN;
	// ウィンドウモード設定 => 定数で切り替え
	m_dx_status.d3d_present_param->Windowed = true;
	//横の解像度
	m_dx_status.d3d_present_param->BackBufferWidth = WIN_W;
	//縦の解像度
	m_dx_status.d3d_present_param->BackBufferHeight = WIN_H;
	//フルスクリーンのリフレッシュレート
	m_dx_status.d3d_present_param->FullScreen_RefreshRateInHz = 0;

	// スワップエフェクト設定 => ディスプレイドライバ依存
	// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	m_dx_status.d3d_present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDeviceの作成
	if (FAILED(m_dx_status.d3d_interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandle_,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		m_dx_status.d3d_present_param,
		&m_dx_status.d3d_device)))
	{
		return false;
	}

	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = m_dx_status.d3d_present_param->BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = m_dx_status.d3d_present_param->BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(m_dx_status.d3d_device->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void DxManager::Transform()
{
	
	// キー入力でカメラの移動 start
	if (Device::KeyOn(VK_RIGHT)) { m_eye_pos.x += 0.1f; }
	if (Device::KeyOn(VK_LEFT)) { m_eye_pos.x -= 0.1f; }
	if (Device::KeyOn(VK_UP)) { m_eye_pos.y += 0.1f; }
	if (Device::KeyOn(VK_DOWN)) { m_eye_pos.y -= 0.1f; }
	// キー入力でカメラの移動 end

	// キー入力でカメラの移動 start
	if (Device::KeyOn('D')) { m_camera_pos.x += 0.1f; m_eye_pos.x += 0.1f; }
	if (Device::KeyOn('A')) { m_camera_pos.x -= 0.1f; m_eye_pos.x -= 0.1f; }
	if (Device::KeyOn('W')) { m_camera_pos.y += 0.1f; m_eye_pos.y += 0.1f; }
	if (Device::KeyOn('S')) { m_camera_pos.y -= 0.1f; m_eye_pos.y -= 0.1f; }
	// キー入力でカメラの移動 end

	//ビュー座標変換用の行列算出 start
	D3DXMatrixIdentity(&m_mat_view);
	D3DXMatrixLookAtLH(&m_mat_view, 
		&m_camera_pos,				// カメラ座標
		&m_eye_pos,					// 注視点座標
		&m_up_vector);				// カメラの上の向きのベクトル
	m_dx_status.d3d_device->SetTransform(D3DTS_VIEW, &m_mat_view);
	//ビュー座標変換用の行列算出 end

	//射影座標変換用の行列算出 start
	D3DVIEWPORT9 vp;
	m_dx_status.d3d_device->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&m_mat_proj,
		D3DXToRadian(60),	// 画角
		aspect,				// アスペクト比
		0.1f,				// near
		10000.0f);			// far
	m_dx_status.d3d_device->SetTransform(D3DTS_PROJECTION, &m_mat_proj);
	//射影座標変換用の行列算出 end
}

void DxManager::StartDraw() {
	m_dx_status.d3d_device->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.0f,	// Zバッファの初期値
		0);		// ステンシルバッファの初期値

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
		TEXT("ＭＳ　Ｐゴシック"),
		&m_font)))
	{
		return false;
	}
	return true;
}