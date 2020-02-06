#ifndef LINE_H_
#define LINE_H_

#include <d3dx9.h>
#include <vector>

struct Line
{
	D3DXVECTOR2 m_Pos;	// ラインの座標変数
	int m_Counter;
};

struct LineManager
{
	float m_Width;				// ラインの太さ(幅)
	D3DXVECTOR2 m_Start;		// スタート位置
	D3DXVECTOR2 m_End;			// エンド位置
	D3DXVECTOR2 m_Center;		// 
	int m_Timer;				// 一定間隔ごとに保存するためのカウント用変数
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
	// コンストラクタ
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

	// デストラクタ
	~LineDrawer() {}

	// ラインの更新
	void UpdateLine();
	void UpdateLineManager();

	// 描画関数
	// こっちを呼ぶ
	void DrawLine();

	// 描画関数
	// こっちのほうは呼ぶ必要はない
	void DrawLine(std::vector<LineDesc>& desc_list);

private:
	LineManager m_LineManager;
};

#endif