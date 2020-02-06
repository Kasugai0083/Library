#include "Line.h"
#include "DirectX.h"


void LineDrawer::UpdateLine()
{
	for (auto& line : m_LineManager.m_Line)
	{
		line.m_Counter--;
	}
}

void LineDrawer::UpdateLineManager()
{
	// 一定フレームごとにオブジェクトを保存する
	m_LineManager.m_Timer++;

	if (m_LineManager.m_Timer % 6 == 0)
	{
		D3DXVECTOR2 new_pos;
		float percent = m_LineManager.m_Timer / 60.0f;

		new_pos.x = (1 - percent) * (1 - percent) * m_LineManager.m_Start.x + 2 * (1 - percent) * percent * m_LineManager.m_Center.x + percent * percent * m_LineManager.m_End.x;
		new_pos.y = (1 - percent) * (1 - percent) * m_LineManager.m_Start.y + 2 * (1 - percent) * percent * m_LineManager.m_Center.y + percent * percent * m_LineManager.m_End.y;

		Line new_line =
		{
			new_pos,
			120,
		};
		m_LineManager.m_Line.push_back(new_line);
	}

	UpdateLine();
}

void LineDrawer::DrawLine()
{
	if (m_LineManager.m_Line.size() < 2)
	{
		return;
	}

	std::vector<LineDesc> desc_list;

	for (int i = 0; i < m_LineManager.m_Line.size() - 1; i++)
	{
		D3DXVECTOR2 direction = D3DXVECTOR2(
			m_LineManager.m_Line[i + 1].m_Pos.x - m_LineManager.m_Line[i].m_Pos.x,
			m_LineManager.m_Line[i + 1].m_Pos.y - m_LineManager.m_Line[i].m_Pos.y);

		float percent = m_LineManager.m_Line[i].m_Counter / 120.0f;

		if (percent <= 0.0f)
		{
			percent = 0.0f;
		}

		for (int j = 0; j < 2; j++)
		{
			// 直角なベクトル
			D3DXVECTOR2 normal = D3DXVECTOR2(-direction.y, direction.x);

			// ベクトルを180度回転する
			if (j == 1)
			{
				normal.x *= -1.0f;
				normal.y *= -1.0f;
			}
			
			// 単位行列化
			float length = sqrtf(normal.x * normal.x + normal.y * normal.y);
			normal.x /= length;
			normal.y /= length;

			D3DXVECTOR2 new_pos = D3DXVECTOR2(direction.x + m_LineManager.m_Width / 2.0f * normal.x,
				direction.y + m_LineManager.m_Width / 2.0f * normal.y);

			new_pos.x += m_LineManager.m_Line[i].m_Pos.x;
			new_pos.y += m_LineManager.m_Line[i].m_Pos.y;

			float alpha = (float)m_LineManager.m_Line[i].m_Counter / 120.0f;
			LineDesc new_desc =
			{
				new_pos,
				alpha > 0.0f ? alpha : 0.0f
			};

			desc_list.push_back(new_desc);
		}
	}

	DrawLine(desc_list);
}

void LineDrawer::DrawLine(std::vector<LineDesc>& desc_list)
{
	D3DXMATRIX mat_trans;
	D3DXMatrixIdentity(&mat_trans);

	D3DXMatrixTranslation(&mat_trans, desc_list[0].m_Pos.x, desc_list[0].m_Pos.y, 0.0f);
	GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat_trans);

	std::vector<VERTEX> vertex_list;

	for (int i = 0; i < desc_list.size(); i++)
	{
		VERTEX new_vertex =
		{
			D3DXVECTOR3(desc_list[i].m_Pos.x,desc_list[i].m_Pos.y, -100.0f),
			D3DXVECTOR2(desc_list[i].m_Pos.x,desc_list[i].m_Pos.y),
		};

		vertex_list.push_back(new_vertex);
	}

	GetD3DDevice()->SetFVF(D3DFVF_XYZ);
	GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, vertex_list.size() - 2, &vertex_list[0], sizeof(VERTEX));
	GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
