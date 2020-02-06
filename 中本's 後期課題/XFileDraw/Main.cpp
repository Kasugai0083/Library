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
		sizeof(WNDCLASSEX),				// 構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,		// クラスのスタイル
		WindowProc,						// ウィンドウプロシージャ
		0,								// 補助メモリ
		0,								// 補助メモリ
		hInstance,						// このプログラムのインスタンスハンドル
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),// アイコン画像
		LoadCursor(NULL, IDC_ARROW),	// カーソル画像
		NULL,							// 背景ブラシ(背景色)
		NULL,							// メニュー名
		TEXT("XFileDraw"),				// クラス名									
		NULL							// 小さいアイコン
	};

	// 構造体の登録
	if (RegisterClassEx(&window_class) == 0)
	{
		return false;
	}

	// ウィンドウ作成
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

	// 読み込みファイル名リスト
	std::string file_name_list[] =
	{
		"Witchwait.x",
		"Sample01.x",
		"map.x"
	};

	// XFile読み込み
	for (int i = 0; i <3; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}

	// XFileオブジェクト作成
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
			-50.0f,							// X座標
			100.0f,							// Y座標
			0.0f,							// 最小値
			100.0f,							// 最大値
			0.0f,							// 現状の値
			100.0f,							// 次の値
			0.0f,							// 速度
			Direction::LeftToRight,			// 進行方向
			SliderTextureNum[0],			// 使用するテクスチャ
		},

		{
			-50.0f,
			150.0f,
			0.0f,							// 最小値
			100.0f,							// 最大値
			0.0f,							// 現状の値
			100.0f,							// 次の値
			0.0f,							// 速度
			Direction::RightToLeft,			// 進行方向
			SliderTextureNum[0],			// 使用するテクスチャ
		},

		{
			-50.0f,
			150.0f,
			0.0f,							// 最小値
			100.0f,							// 最大値
			0.0f,							// 現状の値
			100.0f,							// 次の値
			0.0f,							// 速度
			Direction::UpToDown,			// 進行方向
			SliderTextureNum[1],			// 使用するテクスチャ
		},

		{
			-100.0f,
			150.0f,
			0.0f,							// 最小値
			100.0f,							// 最大値
			0.0f,							// 現状の値
			100.0f,							// 次の値
			0.0f,							// 速度
			Direction::DownToUp,			// 進行方向
			SliderTextureNum[1],			// 使用するテクスチャ
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
			// 描画開始
			StartDraw();

			DrawFont(0.0, 0.0,   "終了 : ESC",    FontSize::Large, FontColor::Black);
			DrawFont(0.0, 60.0,  "視点 : マウス", FontSize::Large, FontColor::Black);
			DrawFont(0.0, 120.0, "移動 : WASD",   FontSize::Large, FontColor::Black);
			DrawFont(0.0, 180.0, "移動 : 移動がまだうまくいっていません", FontSize::Large, FontColor::Black);
			DrawFont(0.0, 240.0, "UP   : SPACE", FontSize::Large, FontColor::Black);
			DrawFont(0.0, 300.0, "DOWN : CTRL", FontSize::Large, FontColor::Black);



			// ライティング設定
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

			// 曲線
			line.DrawLine();
			line2.DrawLine();

			// 描画終了
			EndDraw();
		}
	}

	// 解放

	billboard.ReleaseBillBoard();

	for (int i = 0; i < 2; i++)
	{
		delete(g_pXFileList[file_name_list[i]]);
	}
	return 0;
}

