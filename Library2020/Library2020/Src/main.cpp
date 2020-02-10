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
	DxManager* dx_mgr = DxManager::GetInstance();

	// SceneController
	SceneController::CreateInstance();
	SceneController* scene_ctr = SceneController::GetInstance();


	if (!Device::MakeWindow(WIN_W,WIN_H,"エンジンテスト")) {
		MessageBox(NULL,"ウィンドウ作成失敗",NULL, MB_OK);
	}

	scene_ctr->Init(SceneID::RESULT);



	while (Device::ProcessMessage())
	{
		// ESCAPE キーで終了
		if(Device::KeyPress(VK_ESCAPE)){ PostQuitMessage(0); }

		Device::KeyUpdate();

#if 0
		 //2D描画
		dx_mgr->StartDraw2D();
#else
		// 3D描画
		dx_mgr->StartDraw3D();
#endif

		t_Size font_size{ 32.f,32.f };
		dx_mgr->CreateFontDevice(font_size);

		// シーン制御
		scene_ctr->Update();
		scene_ctr->Draw();

		dx_mgr->EndDraw();

		_CrtDumpMemoryLeaks();

	}

	scene_ctr->Release();

	SceneController::DestroyInstance();
	DxManager::DestroyInstance();

}
