#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <d3d9.h>
#include <d3dx9.h>

class MatrixCalc
{
public:
	// �ړ��s�񐶐�
	D3DXMATRIX* MatrixTranslation(D3DXMATRIX* d3dxmatrix_, float x_, float y_, float z_)
	{
		D3DXMatrixIdentity(d3dxmatrix_);

		d3dxmatrix_->_41 = x_;
		d3dxmatrix_->_42 = y_;
		d3dxmatrix_->_43 = z_;

		return d3dxmatrix_;
	}

	// �g�k�s�񐶐�
	D3DXMATRIX* MatrixScaling(D3DXMATRIX* d3dxmatrix_, float scalex_, float scaley_, float scalez_)
	{
		D3DXMatrixIdentity(d3dxmatrix_);

		d3dxmatrix_->_11 = scalex_;
		d3dxmatrix_->_22 = scaley_;
		d3dxmatrix_->_33 = scalez_;

		return d3dxmatrix_;
	}

	// X����]�s�񐶐�
	D3DXMATRIX* MatrixRotationX(D3DXMATRIX* d3dxmatrix_, float angle_)
	{
		D3DXMatrixIdentity(d3dxmatrix_);

		d3dxmatrix_->_22 = cosf(angle_); d3dxmatrix_->_23 = -sinf(angle_);
		d3dxmatrix_->_32 = sinf(angle_); d3dxmatrix_->_33 = cosf(angle_);
	
		return d3dxmatrix_;
	}

	// Y����]�s�񐶐�
	D3DXMATRIX* MatrixRotationY(D3DXMATRIX* d3dxmatrix_, float angle_)
	{
		D3DXMatrixIdentity(d3dxmatrix_);

		d3dxmatrix_->_11 = cosf(angle_); d3dxmatrix_->_13 = sinf(angle_);
		d3dxmatrix_->_31 = -sinf(angle_); d3dxmatrix_->_33 = cosf(angle_);
		
		return d3dxmatrix_;
	}

	// Z����]�s�񐶐�
	D3DXMATRIX* MatrixRotationZ(D3DXMATRIX* d3dxmatrix_, float angle_)
	{
		D3DXMatrixIdentity(d3dxmatrix_);

		d3dxmatrix_->_11 = cosf(angle_); d3dxmatrix_->_12 = -sinf(angle_);
		d3dxmatrix_->_21 = sinf(angle_); d3dxmatrix_->_22 = cosf(angle_);

		return d3dxmatrix_;
	}

	// �s��̊|���Z
	D3DXMATRIX* MatrixMultiply(D3DXMATRIX* d3dxmatrix_, const D3DXMATRIX* d3dxmatrix_1, const D3DXMATRIX * d3dxmatrix_2)
	{
		*d3dxmatrix_ = *d3dxmatrix_1 * *d3dxmatrix_2;

		return d3dxmatrix_;
	}
};

#endif