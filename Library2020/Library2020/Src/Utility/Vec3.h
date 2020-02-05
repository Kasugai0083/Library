#pragma once

#pragma once

/**
* @file Vec.h
* @brief 3D�̏���ۑ��ł���\���̂̐錾
*/

//=====================================================================//
//! Vector�p�\����(3D��)
//=====================================================================//
typedef struct Vec3
{
	/** Constructor */
	Vec3()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] x ����
	* @param[in] y �c��
	* @param[in] z ���s
	*/
	Vec3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	/**
	* @brief Constructor
	* @param[in] Vec3 �R�s�[�pVec2�f�[�^
	*/
	Vec3(const Vec3& size)
	{
		this->X = size.X;
		this->Y = size.Y;
		this->Z = size.Z;
	}

	float X;	//!< X�l
	float Y;	//!< Y�l
	float Z;	//!< Z�l
}Pos3;
