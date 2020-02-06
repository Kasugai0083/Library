#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "Engine/Graphics/DirectX.h"
#include "Engine/Graphics/XFile.h"
#include "Engine/Graphics/Drawer3D.h"
#include "Engine/Device.h"
#include "Engine/Graphics/Drawer2D.h"
#include "Engine/Graphics/Slider.h"
#include "Engine/Graphics/Grid.h"
#include "Scene/SceneController.h"
#include <string>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>


#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


int APIENTRY WinMain(HINSTANCE ,HINSTANCE, LPSTR, INT)
{


	//DirectXシングルトン作成
	DxManager::CreateInstance();
	DxManager* s_DXManager = DxManager::GetInstance();


	// SceneController
	SceneController::CreateInstance();
	SceneController* s_Controller = SceneController::GetInstance();


	if (!Device::MakeWindow(WIN_W,WIN_H,"エンジンテスト")) {
		MessageBox(NULL,"ウィンドウ作成失敗",NULL, MB_OK);
	}
	s_Controller->Init(SceneID::TITLE);



	while (Device::ProcessMessage())
	{

		Device::KeyUpdate();

#if 1
		 //2D描画
		s_DXManager->StartDraw2D();
#else
		// 3D描画
		s_DXManager->StartDraw3D();
#endif

		t_Size font_size{ 32.f,32.f };
		s_DXManager->CreateFontDevice(font_size);

		// シーン制御
		s_Controller->Update();
		s_Controller->Draw();

		s_DXManager->EndDraw();

		_CrtDumpMemoryLeaks();
	}


	s_Controller->Release();

	SceneController::DestroyInstance();
	DxManager::DestroyInstance();

}
