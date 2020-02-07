#pragma once

#include "../../Utility/Vec3.h"
#include "Drawer2D.h"
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
struct t_Line
{
	Vec3 pos;
	int counter;
};

/**
* @brief ���̃X�e�[�^�X���Ǘ�
* @param width	���̕�
* @param start	���̊J�n�_
* @param end		���̏I�_�H
* @param center	���̒��ԓ_�H
* @param timer	�o�߃t���[����ۑ�
* @param line		�ʒu���ƃ^�C�}�[
*/
struct t_LineManager 
{
	float width;				
	Vec3 start;				
	Vec3 end;					
	Vec3 center;				
	int timer;				
	std::vector<t_Line> line;	
};

/**
* @brief ���̈ʒu���ƐF�ʔZ�x��ۑ�
*/
struct t_LineDesc 
{
	Vec3 pos;
	float alpha;
};

class Drawer3D;

class LineDrawer {
public:

	/**
	* @brief �R���X�g���N�^
	* @param start	���̊J�n�_
	* @param center ���̒��ԓ_
	* @param end	���̏I�_
	*/
	LineDrawer(Vec3 start_, Vec3 center_,Vec3 end_)
	{
		// 10.f �ł����`�悳��Ȃ�
		// �����FWidth���グ��Ƃǂ�ǂ񍂂��ʒu�ŕ`�悳���
		// ������T��
		// �D�� Width �̒l�̔�������Z���Ă��邽�߁A�ʒu���ꂪ�N���Ă���Ǝv����
		m_line_mgr.width = 20.0f;
		m_line_mgr.line.clear();
		m_line_mgr.start = start_;
		m_line_mgr.end = end_;
		m_line_mgr.center = center_;
		m_line_mgr.timer = 0;

		t_Line line =
		{
			m_line_mgr.start,
			120,
		};
		m_line_mgr.line.push_back(line);
	}

	/**
	* @brief �U�t���[�����Ɏ��̐������쐬����
	*/
	void UpdateLineManager();

	/**
	* @brief �Ȑ��̕`��
	*/
	void DrawLine();

private:
	void UpdateLine(); 	//!< @brief counter �����Z����

private:
	t_LineManager m_line_mgr;	//!< @brief �Ȑ��̏����Ǘ�

	Drawer2D m_drawer2d;			//!< @brief �`��֐����Ăяo�����߂Ɏg�p

};