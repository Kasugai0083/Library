#ifndef LINE_H_
#define LINE_H_

#include <d3dx9.h>
#include <vector>

struct Line
{
	D3DXVECTOR2 m_Pos;	// ���C���̍��W�ϐ�
	int m_Counter;
};

struct LineManager
{
	float m_Width;				// ���C���̑���(��)
	D3DXVECTOR2 m_Start;		// �X�^�[�g�ʒu
	D3DXVECTOR2 m_End;			// �G���h�ʒu
	D3DXVECTOR2 m_Center;		// 
	int m_Timer;				// ���Ԋu���Ƃɕۑ����邽�߂̃J�E���g�p�ϐ�
	std::vector<Line> m_Line;	// 
};

struct LineDesc
{
	D3DXVECTOR2 m_Pos;			// 
	float m_Alpha;
};

class LineDrawer
{
public:
	// �R���X�g���N�^
	LineDrawer(D3DXVECTOR2 start_, D3DXVECTOR2 end_) {
		m_LineManager.m_Width = 5.0f;
		m_LineManager.m_Line.clear();
		m_LineManager.m_Start  = start_;
		m_LineManager.m_End    = end_;
		m_LineManager.m_Center = D3DXVECTOR2(100, 100);
		m_LineManager.m_Timer  = 0;

		Line line =
		{
			m_LineManager.m_Start,
			120,
		};
		m_LineManager.m_Line.push_back(line);
	}

	// �f�X�g���N�^
	~LineDrawer() {}

	// ���C���̍X�V
	void UpdateLine();
	void UpdateLineManager();

	// �`��֐�
	// ���������Ă�
	void DrawLine();

	// �`��֐�
	// �������̂ق��͌ĂԕK�v�͂Ȃ�
	void DrawLine(std::vector<LineDesc>& desc_list);

private:
	LineManager m_LineManager;
};

#endif