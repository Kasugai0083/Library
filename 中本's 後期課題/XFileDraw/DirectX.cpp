#include "DirectX.h"
#include "Input.h"

#include <Windows.h>
#include <string>
#include <map>

// グローバル変数
TEXTURE_DATA g_TextureList[MAX_TEXTURE_NUM];

LPDIRECT3D9 g_pD3DInterface;								// DirectXインターフェース
D3DPRESENT_PARAMETERS *g_pD3DPresentParam;					// プレゼントパラメータ
LPDIRECT3DDEVICE9 g_pD3DDevice;								// デバイス
std::map<std::string, LPDIRECT3DTEXTURE9> g_xFileTextureList;	// テクスチャリスト

static LPD3DXFONT g_FontList[FontSize::FontSizeMax];	// フォントデバイスリスト

/*
	DirectXの初期化
		戻り値：
			初期化結果
				成功：
					true
				失敗：
					false
		引数：
			HWND window_handle：
				ウィンドウハンドル
		内容：
			DirectXの初期化を行う
*/
bool InitDirectX(HWND window_handle, HINSTANCE hInstans)
{
	// インターフェース作成
	g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DInterface == NULL)
	{
		// 作成失敗
		return false;
	}

	if (InitInput(hInstans, window_handle) == false)
	{
		return false;
	}

	// プレゼントパラメータ設定
	g_pD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (g_pD3DPresentParam == NULL)
	{
		return false;
	}
	ZeroMemory(g_pD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// バックバッファの数 => 1
	g_pD3DPresentParam->BackBufferCount = 1;
	// バックバッファのフォーマット => D3DFMT_UNKNOWN(フォーマットを知りません)
	g_pD3DPresentParam->BackBufferFormat = D3DFMT_A8R8G8B8;
	// ウィンドウモード設定 => 定数で切り替え
	g_pD3DPresentParam->Windowed = false;
	//横の解像度
	g_pD3DPresentParam->BackBufferWidth = 1920;
	//縦の解像度
	g_pD3DPresentParam->BackBufferHeight = 1080;
	//フルスクリーンのリフレッシュレート
	g_pD3DPresentParam->FullScreen_RefreshRateInHz = 60.f;

	// スワップエフェクト設定 => ディスプレイドライバ依存
	// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	g_pD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// aでプルとステンシルバッファの有効設定
	g_pD3DPresentParam->EnableAutoDepthStencil = true;

	// デプスとステンシルバッファのフォーマット設定
	g_pD3DPresentParam->AutoDepthStencilFormat = D3DFMT_D24S8;

	// DirectDeviceの作成
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		g_pD3DPresentParam,
		&g_pD3DDevice)))
	{
		return false;
	}

	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = g_pD3DPresentParam->BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = g_pD3DPresentParam->BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(g_pD3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	if (CreateFontDevice() == false)
	{
		return false;
	}

	return true;
}

/*
	座標変換設定
		戻り値：
			なし
		引数：
			なし
		内容：
			ビュー座標、プロジェクション座標変換を行う
*/
void Transform(void)
{
	D3DXMATRIX matProj, matView;

	//ビュー座標変換用の行列算出 start
	D3DXVECTOR3 camera_pos(0.0f, 0.0f, -10.0f); // カメラ位置
	D3DXVECTOR3 eye_pos(0.0f, 0.0f, 0.0f);		// 注視点
	D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// カメラの向き

	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView, 
		&camera_pos,				// カメラ座標
		&eye_pos,					// 注視点座標
		&up_vector);				// カメラの上の向きのベクトル
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//ビュー座標変換用の行列算出 end

	//射影座標変換用の行列算出 start
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// 画角
		aspect,				// アスペクト比
		0.1f,				// near
		100.0f);			// far
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//射影座標変換用の行列算出 end
}


/*
	描画開始
		戻り値：
			なし
		引数：
			なし
		内容：
			描画を始めるための処理を行う
*/
void StartDraw(void)
{
	// 青色でレンダリングターゲットをクリア
	g_pD3DDevice->Clear(0, NULL, 
		// クリアするバッファの設定
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		// クリアカラー
		D3DCOLOR_XRGB(0, 0, 255),
		// デプスバッファの初期値
		1.0f,
		// ステンシルバッファの初期値
		0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->LightEnable(0, false);
	
	g_pD3DDevice->BeginScene();
}

/*
	描画終了
		戻り値：
			なし
		引数：
			なし
		内容：
			描画終了のための処理を行う
*/
void EndDraw(void)
{
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*
	ライトの設定
		戻り値：
			なし
		引数：
			なし
		内容：
			3D空間で使用するライトの設定を行う
*/
void SetLighting(void)
{
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, 0, 1);
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vec_direction);
	light.Range = 200.0f;
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, false);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

const LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}

int LoadTexture(const char* fileName_, int useId_)
{
	int select_id = -1;

	if (useId_ < 0 || useId_ >= MAX_TEXTURE_NUM)
	{
		useId_ = -1;
	}

	if (useId_ == -1)
	{
		for (int i = 0; i < MAX_TEXTURE_NUM; ++i)
		{
			if (g_TextureList[i].m_pTexture == nullptr)
			{
				select_id = i;
				break;
			}
		}
	}
	else {
		if (g_TextureList[useId_].m_pTexture != nullptr)
		{
			ReleaseTexture(useId_);
		}

		select_id = useId_;
	}

	if (select_id == -1)
	{
		return -1;
	}
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(fileName_, &info);

	if (FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice,
		fileName_,
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		NULL,
		NULL,
		&g_TextureList[select_id].m_pTexture)))
	{
		return -1;
	}
	else {
		// テクスチャサイズの取得
		D3DSURFACE_DESC desc;

		if (FAILED(g_TextureList[select_id].m_pTexture->GetLevelDesc(0, &desc)))
		{
			g_TextureList[select_id].m_pTexture->Release();
			g_TextureList[select_id].m_pTexture = NULL;
			return -1;
		}
		g_TextureList[select_id].m_Width = desc.Width;
		g_TextureList[select_id].m_Height = desc.Height;
	}

	return select_id;
}

bool IsUseTexture(int textureId_)
{
	if (g_TextureList[textureId_].m_pTexture != NULL)
	{
		return true;
	}

	return false;
}

const TEXTURE_DATA* GetTextureData(int textureId_)
{
	return &g_TextureList[textureId_];
}

void ReleaseTexture(int textureId_)
{
	if (textureId_ < 0 ||
		textureId_ >= MAX_TEXTURE_NUM)
	{
		return;
	}

	if (g_TextureList[textureId_].m_pTexture != NULL)
	{
		g_TextureList[textureId_].m_pTexture->Release();
		g_TextureList[textureId_].m_pTexture = NULL;
	}
}

void DrawUVMappingTexture(float x, float y, TEXTURE_DATA* texture_data, float texture_x, float texture_y, float rect_width, float rect_height)
{
	float uv_left   = texture_x / texture_data->m_Width;
	float uv_right  = (texture_x + rect_width) / texture_data->m_Width;
	float uv_top    = texture_y / texture_data->m_Height;
	float uv_bottom = (texture_y + rect_height) / texture_data->m_Height;

	// 三角形を描画 start
	VERTEX v[] =
	{
		{ D3DXVECTOR3(x, y, 0.0f),				D3DXVECTOR2(uv_left, uv_top) },
		{ D3DXVECTOR3(x + rect_width, y, 0.0f), D3DXVECTOR2(uv_right, uv_top) },
		{ D3DXVECTOR3(x, y + rect_height, 0.0f), D3DXVECTOR2(uv_left, uv_bottom) },
		{ D3DXVECTOR3(x + rect_width, y + rect_height, 0.0f), D3DXVECTOR2(uv_right, uv_bottom) },
	};
	
	
	GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GetD3DDevice()->SetRenderState(D3DRS_ZENABLE, true);
	GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE); // RHWで無い頂点はLIGHTが効くので無効にしておく
	GetD3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	GetD3DDevice()->SetTexture(0, texture_data->m_pTexture);
	GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(VERTEX));
}

TEXTURE_DATA* GetTexture(int texture_id)
{
	if (g_TextureList[texture_id].m_pTexture == nullptr) { return nullptr; }


	return &g_TextureList[texture_id];
}

bool CreateFontDevice()
{
	int size_list[] =
	{
		SMALL_FONT_SIZE,
		REGULAR_FONT_SIZE,
		LARGE_FONT_SIZE
	};

	for (int i = 0; i < FontSize::FontSizeMax; i++)
	{
		if (FAILED(D3DXCreateFont(g_pD3DDevice,
			size_list[i],
			size_list[i] / 2,
			FW_REGULAR,
			NULL,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			TEXT("ＭＳ　Ｐゴシック"),
			&g_FontList[i])))
		{
			return false;
		}
	}

	return true;
}

void DrawFont(float pos_x, float pos_y, const char* text, FontSize size, FontColor color)
{
	RECT rect =
	{
		(long)pos_x,
		(long)pos_y,
		(long)pos_x + 1500,
		(long)pos_y + 200,
	};

	int r, g, b;
	r = g = b = 255;

	if (color == FontColor::Black)
	{
		r = g = b = 0;
	}
	else if (color == FontColor::Red)
	{
		r = 255;
		g = b = 0;
	}
	else if (color == FontColor::Yellow)
	{
		r = 255;
		g = 215;
		b = 20;
	}

	g_FontList[size]->DrawTextA(
		NULL,
		text,
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(r, g, b)
	);
}
