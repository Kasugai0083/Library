#ifndef BILLBORAD_H_
#define BILLBORAD_H_

#include <d3dx9.h>


class BillBorad
{
public:
	const D3DXVECTOR3* GetBillBoradPosPointer();

	/*
		�r���{�[�h�������֐�
	*/
	void InitBillBoard();

	/*
		�r���{�[�h�̉���֐�
	*/
	void ReleaseBillBoard();

	/*
		�r���{�[�h�`��p�֐�
	*/
	void DrawBillBoard(D3DXMATRIX* viewMat_);

	/*
		��r�p�̃r���{�[�h���s���Ă��Ȃ��`��֐�
	*/
	void DrawNotBillBoard();

private:
	// ���W
	D3DXVECTOR3 m_BillBoardPos;
	// �e�N�X�`���ԍ�
	int			m_BillBoardTextureId;
	// �e�N�X�`�����W
	D3DXVECTOR2 m_TexturePos;
	// �e�N�X�`���T�C�Y
	D3DXVECTOR2 m_TextureSize;

};

#endif