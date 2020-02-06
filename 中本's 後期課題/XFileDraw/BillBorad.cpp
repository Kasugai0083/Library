#include "BillBorad.h"
#include "DirectX.h"

const D3DXVECTOR3* BillBorad::GetBillBoradPosPointer()
{
	return &m_BillBoardPos;
}

void BillBorad::InitBillBoard()
{
	m_BillBoardTextureId = LoadTexture("sample.png");
	m_BillBoardPos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	m_TextureSize  = D3DXVECTOR2(0.0f, 0.0f);
	m_TextureSize  = D3DXVECTOR2(128.0f, 128.0f);
}

void BillBorad::ReleaseBillBoard()
{
	ReleaseTexture(m_BillBoardTextureId);
}

void BillBorad::DrawBillBoard(D3DXMATRIX* viewMat_)
{
	D3DXMATRIX view_mat, world, trans;

	D3DXMatrixIdentity(&view_mat);
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);

	D3DXMatrixTranslation(&trans, m_BillBoardPos.x, m_BillBoardPos.y, m_BillBoardPos.z);
	

	D3DXMatrixInverse(&view_mat, nullptr, viewMat_);

	view_mat._41 = 0.0f;
	view_mat._42 = 0.0f;
	view_mat._43 = 0.0f;

	world = view_mat * trans;

	GetD3DDevice()->SetTransform(D3DTS_WORLD, &world);

	float left_tu   = 0.0f;
	float right_tu  = 1.0f;
	float top_tv    = 0.0f;
	float bottom_tv = 1.0f;
	const TEXTURE_DATA* texture_data = GetTextureData(m_BillBoardTextureId);

	float harf_x = texture_data->m_Width / 2.0f;
	float harf_y = texture_data->m_Height / 2.0f;

	// 三角形を描画
	VERTEX v[] =
	{
		{ D3DXVECTOR3(-harf_x, harf_y, 0.0f),  D3DXVECTOR2(left_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, harf_y, 0.0f),   D3DXVECTOR2(right_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, -harf_y, 0.0f),  D3DXVECTOR2(right_tu, bottom_tv) },
		{ D3DXVECTOR3(-harf_x, -harf_y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },
	};

	// 法線を設定していないのでライティングはなし
	GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHWで無い頂点はLIGHTが効くので無効にしておく
	GetD3DDevice()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	// ⑦．板ポリ描画
	// 頂点構造の指定
	GetD3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	GetD3DDevice()->SetTexture(0, texture_data->m_pTexture);
	GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));
}

void BillBorad::DrawNotBillBoard()
{
	D3DXMATRIXA16 world, trans;

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);

	// 移動
	D3DXMatrixTranslation(&trans, m_BillBoardPos.x, m_BillBoardPos.y + 150.0f, m_BillBoardPos.z);
	world = trans;

	GetD3DDevice()->SetTransform(D3DTS_WORLD, &world);

	/////////////////////////////////////////////////////
	float left_tu = 0.0f;
	float right_tu = 1.0f;
	float top_tv = 0.0f;
	float bottom_tv = 1.0f;
	const TEXTURE_DATA* texture_data = GetTextureData(m_BillBoardTextureId);

	float harf_x = texture_data->m_Width / 2.0f;
	float harf_y = texture_data->m_Height / 2.0f;

	// 三角形を描画 start
	VERTEX v[] =
	{
		{ D3DXVECTOR3(-harf_x, harf_y, 0.0f),  D3DXVECTOR2(left_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, harf_y, 0.0f),   D3DXVECTOR2(right_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, -harf_y, 0.0f),  D3DXVECTOR2(right_tu, bottom_tv) },
		{ D3DXVECTOR3(-harf_x, -harf_y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },
	};

	GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE); // RHWで無い頂点はLIGHTが効くので無効にしておく
	GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	// 頂点構造の指定
	GetD3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	GetD3DDevice()->SetTexture(0, texture_data->m_pTexture);
	GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));
}