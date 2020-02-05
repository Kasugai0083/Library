#pragma once

#include <d3d9.h>
#include <d3dx9.h>

/**
* @brief
* �s��n�̎���֐�
*/

namespace HandMade {
	
	/**
	* @brief �s���p�������W�ړ�
	* @out matrix_ �ړ�������I�u�W�F�N�g�̍s��
	* @in x_ �I�u�W�F�N�g�ɉ�����X���W�̒l
	* @in y_ �I�u�W�F�N�g�ɉ�����Y���W�̒l
	* @in z_ �I�u�W�F�N�g�ɉ�����Z���W�̒l
	*/
	void Translation(D3DXMATRIX* matrix_, float x_, float y_, float z_);
	
	/**
	* @brief �r���{�[�h������
	* @out out_ �I�u�W�F�N�g�̃��[���h�s��
	* @in in_ DirectX �� View �s��
	*/
	void BillBoard(D3DXMATRIX* out_, D3DXMATRIX* in_);

	/**
	* @brief �s���p�����I�u�W�F�N�g�̊g�k
	* @out matrix_ �g�k������I�u�W�F�N�g�̍s��
	* @in x_ X���̊g�k��
	* @in y_ Y���̊g�k��
	* @in z_ Z���̊g�k��
	*/
	void Scaling(D3DXMATRIX* matrix_, float x_, float y_, float z_);

	/**
	* @biref �s���p�����I�u�W�F�N�g�̉�]
	* @out matrix_ ��]������I�u�W�F�N�g�̍s��
	* @in radian_ ��]������p�x(�x���@)
	*/
	void RotationX(D3DXMATRIX* matrix_, float radian_);
	void RotationY(D3DXMATRIX* matrix_, float radian_);
	void RotationZ(D3DXMATRIX* matrix_, float radian_);

}

