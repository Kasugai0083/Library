#include "DirectX.h"
#include "Input.h"

#include <Windows.h>
#include <string>
#include <map>

// �O���[�o���ϐ�
TEXTURE_DATA g_TextureList[MAX_TEXTURE_NUM];

LPDIRECT3D9 g_pD3DInterface;								// DirectX�C���^�[�t�F�[�X
D3DPRESENT_PARAMETERS *g_pD3DPresentParam;					// �v���[���g�p�����[�^
LPDIRECT3DDEVICE9 g_pD3DDevice;								// �f�o�C�X
std::map<std::string, LPDIRECT3DTEXTURE9> g_xFileTextureList;	// �e�N�X�`�����X�g

static LPD3DXFONT g_FontList[FontSize::FontSizeMax];	// �t�H���g�f�o�C�X���X�g

/*
	DirectX�̏�����
		�߂�l�F
			����������
				�����F
					true
				���s�F
					false
		�����F
			HWND window_handle�F
				�E�B���h�E�n���h��
		���e�F
			DirectX�̏��������s��
*/
bool InitDirectX(HWND window_handle, HINSTANCE hInstans)
{
	// �C���^�[�t�F�[�X�쐬
	g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DInterface == NULL)
	{
		// �쐬���s
		return false;
	}

	if (InitInput(hInstans, window_handle) == false)
	{
		return false;
	}

	// �v���[���g�p�����[�^�ݒ�
	g_pD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (g_pD3DPresentParam == NULL)
	{
		return false;
	}
	ZeroMemory(g_pD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	g_pD3DPresentParam->BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	g_pD3DPresentParam->BackBufferFormat = D3DFMT_A8R8G8B8;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	g_pD3DPresentParam->Windowed = false;
	//���̉𑜓x
	g_pD3DPresentParam->BackBufferWidth = 1920;
	//�c�̉𑜓x
	g_pD3DPresentParam->BackBufferHeight = 1080;
	//�t���X�N���[���̃��t���b�V�����[�g
	g_pD3DPresentParam->FullScreen_RefreshRateInHz = 60.f;

	// �X���b�v�G�t�F�N�g�ݒ� => �f�B�X�v���C�h���C�o�ˑ�
	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	g_pD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// a�Ńv���ƃX�e���V���o�b�t�@�̗L���ݒ�
	g_pD3DPresentParam->EnableAutoDepthStencil = true;

	// �f�v�X�ƃX�e���V���o�b�t�@�̃t�H�[�}�b�g�ݒ�
	g_pD3DPresentParam->AutoDepthStencilFormat = D3DFMT_D24S8;

	// DirectDevice�̍쐬
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		g_pD3DPresentParam,
		&g_pD3DDevice)))
	{
		return false;
	}

	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;
	// �r���[�|�[�g�̕�
	view_port.Width = g_pD3DPresentParam->BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = g_pD3DPresentParam->BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// �r���[�|�[�g�ݒ�
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
	���W�ϊ��ݒ�
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			�r���[���W�A�v���W�F�N�V�������W�ϊ����s��
*/
void Transform(void)
{
	D3DXMATRIX matProj, matView;

	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXVECTOR3 camera_pos(0.0f, 0.0f, -10.0f); // �J�����ʒu
	D3DXVECTOR3 eye_pos(0.0f, 0.0f, 0.0f);		// �����_
	D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// �J�����̌���

	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView, 
		&camera_pos,				// �J�������W
		&eye_pos,					// �����_���W
		&up_vector);				// �J�����̏�̌����̃x�N�g��
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//�r���[���W�ϊ��p�̍s��Z�o end

	//�ˉe���W�ϊ��p�̍s��Z�o start
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// ��p
		aspect,				// �A�X�y�N�g��
		0.1f,				// near
		100.0f);			// far
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//�ˉe���W�ϊ��p�̍s��Z�o end
}


/*
	�`��J�n
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			�`����n�߂邽�߂̏������s��
*/
void StartDraw(void)
{
	// �F�Ń����_�����O�^�[�Q�b�g���N���A
	g_pD3DDevice->Clear(0, NULL, 
		// �N���A����o�b�t�@�̐ݒ�
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		// �N���A�J���[
		D3DCOLOR_XRGB(0, 0, 255),
		// �f�v�X�o�b�t�@�̏����l
		1.0f,
		// �X�e���V���o�b�t�@�̏����l
		0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->LightEnable(0, false);
	
	g_pD3DDevice->BeginScene();
}

/*
	�`��I��
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			�`��I���̂��߂̏������s��
*/
void EndDraw(void)
{
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*
	���C�g�̐ݒ�
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			3D��ԂŎg�p���郉�C�g�̐ݒ���s��
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
		// �e�N�X�`���T�C�Y�̎擾
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

	// �O�p�`��`�� start
	VERTEX v[] =
	{
		{ D3DXVECTOR3(x, y, 0.0f),				D3DXVECTOR2(uv_left, uv_top) },
		{ D3DXVECTOR3(x + rect_width, y, 0.0f), D3DXVECTOR2(uv_right, uv_top) },
		{ D3DXVECTOR3(x, y + rect_height, 0.0f), D3DXVECTOR2(uv_left, uv_bottom) },
		{ D3DXVECTOR3(x + rect_width, y + rect_height, 0.0f), D3DXVECTOR2(uv_right, uv_bottom) },
	};
	
	
	GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GetD3DDevice()->SetRenderState(D3DRS_ZENABLE, true);
	GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE); // RHW�Ŗ������_��LIGHT�������̂Ŗ����ɂ��Ă���
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
			TEXT("�l�r�@�o�S�V�b�N"),
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
