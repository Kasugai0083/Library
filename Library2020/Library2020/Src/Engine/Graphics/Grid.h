#pragma once

#include "../../Utility/Vec3.h"
#include "Drawer2D.h"
#include "Drawer3D.h"
#include <d3dx9.h>
#include <vector>

/*
	�E�Ȑ��̕`��
	�ȉ��̗�����Q�l�ɋȐ��̕`�������
	�@�D����I�u�W�F�N�g�̍��W�����t���[�����ɕۑ�����
	�A�D�ۑ�����Ă���W�Ǝ��̍��W�Ńx�N�g�����Z�o����
	�B�D�A�̃x�N�g���ɑ΂��Ē��p�ȃx�N�g�����Z�o����
	�C�D�B�̃x�N�g����P�ʃx�N�g���ɂ���
	�D�D���̕� / 2 ���C�̃x�N�g���Ɋ|����
	�E�D�D�̃x�N�g���ɍ��W�𑫂����V�������W�����

	�F�D�D�̃x�N�g����180�x��]����
	�G�D�F�̃x�N�g���ƍ��W�𑫂����V�������W�����

	�H�D�A�`�G���J��Ԃ���TriangleStrip�ŕ`�悷�邽�߂̒��_�̉�����
*/

/**
* @brief 
* �Ȑ��̏����Ǘ�
*/

/**
* ���̍��W�ƌo�߃t���[����ۑ�
*/
struct Line
{
	Vec3 m_Pos;
	int m_Counter;
};

/**
* @brief ���̃X�e�[�^�X���Ǘ�
* @param m_Width	���̕�
* @param m_Start	���̊J�n�_
* @param m_End		���̏I�_�H
* @param m_Center	���̒��ԓ_�H
* @param m_Timer	�o�߃t���[����ۑ�
* @param m_Line		�ʒu���ƃ^�C�}�[
*/
struct LineManager 
{
	float m_Width;				
	Vec3 m_Start;				
	Vec3 m_End;					
	Vec3 m_Center;				
	int m_Timer;				
	std::vector<Line>m_Line;	
};

/**
* @brief ���̈ʒu���ƐF�ʔZ�x��ۑ�
*/
struct LineDesc 
{
	Vec3 m_Pos;
	float m_Alpha;
};

//class Drawer3D;

class LineDrawer {
public:

	/**
	* @brief �R���X�g���N�^
	* @param start	���̊J�n�_
	* @param center ���̒��ԓ_
	* @param end	���̏I�_
	*/
	LineDrawer(Vec3 start, Vec3 center,Vec3 end)
	{
		// 10.f �ł����`�悳��Ȃ�
		// �����FWidth���グ��Ƃǂ�ǂ񍂂��ʒu�ŕ`�悳���
		// ������T��
		// �D�� Width �̒l�̔�������Z���Ă��邽�߁A�ʒu���ꂪ�N���Ă���Ǝv����
		m_LineManager.m_Width = 20.0f;
		m_LineManager.m_Line.clear();
		m_LineManager.m_Start = start;
		m_LineManager.m_End = end;
		m_LineManager.m_Center = center;
		m_LineManager.m_Timer = 0;

		Line line =
		{
			m_LineManager.m_Start,
			120,
		};
		m_LineManager.m_Line.push_back(line);
	}

	/**
	* @brief �U�t���[�����Ɏ��̐������쐬����
	*/
	void UpdateLineManager();

	/**
	* @brief �Ȑ��̕`��
	*/
	void DrawLine(Dimendion dim_);

private:
	void UpdateLine(); 	//!< @brief m_Counter �����Z����

private:
	LineManager m_LineManager;	//!< @brief �Ȑ��̏����Ǘ�

	Drawer2D drawer2d;			//!< @brief �`��֐����Ăяo�����߂Ɏg�p
	Drawer3D drawer3d;			//!< @brief �`��֐����Ăяo�����߂Ɏg�p

};