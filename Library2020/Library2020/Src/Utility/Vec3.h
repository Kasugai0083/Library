#pragma once

#pragma once

/**
* @file Vec.h
* @brief 3Dの情報を保存できる構造体の宣言
*/

//=====================================================================//
//! Vector用構造体(3D版)
//=====================================================================//
typedef struct t_Vec3
{
	/** Constructor */
	t_Vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] x 横幅
	* @param[in] y 縦幅
	* @param[in] z 奥行
	*/
	t_Vec3(float x_, float y_, float z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	/**
	* @brief Constructor
	* @param[in] t_Vec3 コピー用Vec2データ
	*/
	t_Vec3(const t_Vec3& size)
	{
		this->x = size.x;
		this->y = size.y;
		this->z = size.z;
	}

	float x;	//!< X値
	float y;	//!< Y値
	float z;	//!< Z値
}Pos3;
