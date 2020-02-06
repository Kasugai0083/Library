#include <windows.h>
#include <map>
#include "DirectX.h"
#include "XFile.h"
#include "Drawer.h"
#include "Camera.h"
#include "BillBorad.h"
#include "Slider.h"
#include "Line.h"

extern std::map<std::string, XFile *>g_pXFileList;

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message_id, wparam, lparam);
		break;
	}

	return 0;
}


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEX),				// �\���̂̃T�C�Y
		CS_HREDRAW | CS_VREDRAW,		// �N���X�̃X�^�C��
		WindowProc,						// �E�B���h�E�v���V�[�W��
		0,								// �⏕������
		0,								// �⏕������
		hInstance,						// ���̃v���O�����̃C���X�^���X�n���h��
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),// �A�C�R���摜
		LoadCursor(NULL, IDC_ARROW),	// �J�[�\���摜
		NULL,							// �w�i�u���V(�w�i�F)
		NULL,							// ���j���[��
		TEXT("XFileDraw"),				// �N���X��									
		NULL							// �������A�C�R��
	};

	// �\���̂̓o�^
	if (RegisterClassEx(&window_class) == 0)
	{
		return false;
	}

	// �E�B���h�E�쐬
	hWnd = CreateWindow(
		TEXT("XFileDraw"),
		TEXT("XFileDraw"),
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
		0,
		0,
		1920,
		1080,
		NULL,
		NULL,
		hInstance,
		NULL);
	
	if (hWnd == NULL)
	{
		return false;
	}

	if (InitDirectX(hWnd, hInstance) == false)
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	ShowCursor(false);

	// �ǂݍ��݃t�@�C�������X�g
	std::string file_name_list[] =
	{
		"Witchwait.x",
		"Sample01.x",
		"map.x"
	};

	// XFile�ǂݍ���
	for (int i = 0; i <3; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}

	// XFile�I�u�W�F�N�g�쐬
	Drawer obj1(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["Witchwait.x"]);

	Drawer mapObj1(
		D3DXVECTOR3(0.0f, -100.0f, 0.0f),
		D3DXVECTOR3(100.0f, 100.0f, 100.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["map.x"]);

	Drawer obj2(
		D3DXVECTOR3(-200.0f, 0.0f, 0.0f),
		D3DXVECTOR3(50.0f, 50.0f, 50.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["Sample01.x"]);

	CAMERA camera(0.0f,0.0f,-250.0f);

	BillBorad billboard;
	billboard.InitBillBoard();


	int SliderTextureNum[2] = {
		LoadTexture("Res/Slider01.png"),
		LoadTexture("Res/Slider02.png"),
	};

	Slider sliders[] =
	{
		{
			-50.0f,							// X���W
			100.0f,							// Y���W
			0.0f,							// �ŏ��l
			100.0f,							// �ő�l
			0.0f,							// ����̒l
			100.0f,							// ���̒l
			0.0f,							// ���x
			Direction::LeftToRight,			// �i�s����
			SliderTextureNum[0],			// �g�p����e�N�X�`��
		},

		{
			-50.0f,
			150.0f,
			0.0f,							// �ŏ��l
			100.0f,							// �ő�l
			0.0f,							// ����̒l
			100.0f,							// ���̒l
			0.0f,							// ���x
			Direction::RightToLeft,			// �i�s����
			SliderTextureNum[0],			// �g�p����e�N�X�`��
		},

		{
			-50.0f,
			150.0f,
			0.0f,							// �ŏ��l
			100.0f,							// �ő�l
			0.0f,							// ����̒l
			100.0f,							// ���̒l
			0.0f,							// ���x
			Direction::UpToDown,			// �i�s����
			SliderTextureNum[1],			// �g�p����e�N�X�`��
		},

		{
			-100.0f,
			150.0f,
			0.0f,							// �ŏ��l
			100.0f,							// �ő�l
			0.0f,							// ����̒l
			100.0f,							// ���̒l
			0.0f,							// ���x
			Direction::DownToUp,			// �i�s����
			SliderTextureNum[1],			// �g�p����e�N�X�`��
		},
	};

	LineDrawer line(D3DXVECTOR2(0.0f, -600.0f), D3DXVECTOR2(600.0f, 600.0f));
	LineDrawer line2(D3DXVECTOR2(100.0f, -600.0f), D3DXVECTOR2(-600.0f, 600.0f));

	while (!GetKeyDown(KEY_INFO::ESC_KEY))
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			KeyStateUpdate();
			UpdateInput();

			camera.Update();
			camera.Move();
			camera.MouseRotate();

			static int count = 0;
			count++;

			for (int i = 0; i < 4; i++)
			{
				UpdateSliderCurrentValue(sliders[i]);

				if (count % 120 == 0)
				{
					UpdateSliderNextValue(sliders[i].MaxValue, sliders[i]);
				}
				else if (count % 60 == 0)
				{
					UpdateSliderNextValue(sliders[i].MinValue, sliders[i]);
				}
			}

			line.UpdateLineManager();
			line2.UpdateLineManager();

			/////////////////////////////////////////////////////////
			// �`��J�n
			StartDraw();

			DrawFont(0.0, 0.0,   "�I�� : ESC",    FontSize::Large, FontColor::Black);
			DrawFont(0.0, 60.0,  "���_ : �}�E�X", FontSize::Large, FontColor::Black);
			DrawFont(0.0, 120.0, "�ړ� : WASD",   FontSize::Large, FontColor::Black);
			DrawFont(0.0, 180.0, "�ړ� : �ړ����܂����܂������Ă��܂���", FontSize::Large, FontColor::Black);
			DrawFont(0.0, 240.0, "UP   : SPACE", FontSize::Large, FontColor::Black);
			DrawFont(0.0, 300.0, "DOWN : CTRL", FontSize::Large, FontColor::Black);



			// ���C�e�B���O�ݒ�
			SetLighting();

			// XFile
			obj1.Draw();
			mapObj1.Draw();
			obj2.Draw();

			// Billboard
			billboard.DrawBillBoard(camera.GetView());
			billboard.DrawNotBillBoard();

			// Slider
			for (int i = 0; i < 4; i++)
			{
				DrawSliderUVMappingVersion(sliders[i]);
			}

			// �Ȑ�
			line.DrawLine();
			line2.DrawLine();

			// �`��I��
			EndDraw();
		}
	}

	// ���

	billboard.ReleaseBillBoard();

	for (int i = 0; i < 2; i++)
	{
		delete(g_pXFileList[file_name_list[i]]);
	}
	return 0;
}

