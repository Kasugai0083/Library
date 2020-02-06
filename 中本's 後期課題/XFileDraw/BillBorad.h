#ifndef BILLBORAD_H_
#define BILLBORAD_H_

#include <d3dx9.h>


class BillBorad
{
public:
	const D3DXVECTOR3* GetBillBoradPosPointer();

	/*
		ビルボード初期化関数
	*/
	void InitBillBoard();

	/*
		ビルボードの解放関数
	*/
	void ReleaseBillBoard();

	/*
		ビルボード描画用関数
	*/
	void DrawBillBoard(D3DXMATRIX* viewMat_);

	/*
		比較用のビルボードを行っていない描画関数
	*/
	void DrawNotBillBoard();

private:
	// 座標
	D3DXVECTOR3 m_BillBoardPos;
	// テクスチャ番号
	int			m_BillBoardTextureId;
	// テクスチャ座標
	D3DXVECTOR2 m_TexturePos;
	// テクスチャサイズ
	D3DXVECTOR2 m_TextureSize;

};

#endif