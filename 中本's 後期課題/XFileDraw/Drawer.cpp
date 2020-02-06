#include "XFile.h"
#include "Drawer.h"
#include "Input.h"
#include "Calculator.h"

extern LPDIRECT3DDEVICE9 g_pD3DDevice;

/*
	描画
		戻り値：
			なし
		引数：
			なし
		内容：
			ワールド座標行列を作成してXFileを描画する
*/
void Drawer::Draw(void)
{
	static MatrixCalc calc;

	// ワールド座標行列作成 start
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMATRIX rot_y;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixIdentity(&scale_matrix);

	calc.MatrixScaling(&scale_matrix, m_Scale.x, m_Scale.y, m_Scale.z);
	calc.MatrixTranslation(&trans_matrix, m_Pos.x, m_Pos.y, m_Pos.z);
	//// 回転行列を追加
	////D3DXMatrixRotationY(&rot_y, D3DXToRadian(m_Angle.y));
	//calc.MatrixRotationZ(&rot_y, D3DXToRadian(m_Angle.y));
	//D3DXMatrixScaling(&scale_matrix, m_Scale.x, m_Scale.y, m_Scale.z);
	//D3DXMatrixTranslation(&trans_matrix, m_Pos.x, m_Pos.y, m_Pos.z);

	world_matrix *= scale_matrix * trans_matrix;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);
	// ワールド座標行列作成 end

	if (m_pXFile != NULL)
	{
		m_pXFile->Draw();
	}
}

void Drawer::Update()
{
}