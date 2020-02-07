#include "Grid.h"
#include "Drawer2D.h"

// m_Counter を減算する
void LineDrawer::UpdateLine() {
	for (auto& line : m_LineManager.m_Line)
	{
		line.m_Counter -= 0;
	}
}

void LineDrawer::UpdateLineManager() {
	// m_Timer を加算
	m_LineManager.m_Timer++;

	// 6 flame 後、行われる処理
	if (m_LineManager.m_Timer % 6 == 0)
	{
		Vec3 new_pos;

		// persent <= こいつは何？
		// 毎フレーム加算される Timer に 1秒 => 60フレームが割られている
		// persent は時間に関わる割合であると予測できる
		// persent の値を変更すると =>
		// 曲線の描画速度があがる + 座標が変わる(問題！)
		float percent = m_LineManager.m_Timer / 15.0f;

		// 仮説①：始点と中間点、終点を結ぶ曲線の計算をしている
		// 仮説②：ブレンドする値は始点・中間点・終点といった関わりではなく、
		//		   曲線の曲がり具合を設定するものである
		new_pos.x = 
			(1 - percent) 
			* (1 - percent) 
			* m_LineManager.m_Start.x + 2 
			* (1 - percent) 
			* percent 
			* m_LineManager.m_Center.x + percent 
			* percent 
			* m_LineManager.m_End.x;

		new_pos.y = 
			(1 - percent) 
			* (1 - percent) 
			* m_LineManager.m_Start.y + 2 
			* (1 - percent) * percent 
			* m_LineManager.m_Center.y + percent 
			* percent 
			* m_LineManager.m_End.y;

		new_pos.z = 
			(1 - percent) 
			* (1 - percent) 
			* m_LineManager.m_Start.z + 2 
			* (1 - percent) * percent 
			* m_LineManager.m_Center.z + percent 
			* percent 
			* m_LineManager.m_End.z;

		Line new_line =
		{
			new_pos,
			120,
		};
		m_LineManager.m_Line.push_back(new_line);
	}

	UpdateLine();
}

void LineDrawer::DrawLine(Dimendion dim_) {
	if (m_LineManager.m_Line.size() <= 2)
	{
		return;
	}

	std::vector<t_LineDesc> desc_list;

	for (int i = 0; i < (int)m_LineManager.m_Line.size() - 1; i++)
	{
		Vec3 direction = Vec3(
			// ②.保存されてる座標と次の座標でベクトルを算出する
			m_LineManager.m_Line[i + 1].m_Pos.x - m_LineManager.m_Line[i].m_Pos.x,
			m_LineManager.m_Line[i + 1].m_Pos.y - m_LineManager.m_Line[i].m_Pos.y,
			m_LineManager.m_Line[i + 1].m_Pos.z - m_LineManager.m_Line[i].m_Pos.z
		);


		// ⑧．⑦のベクトルと座標を足した新しい座標を作る
		for (int j = 0; j < 2; j++)
		{
			// 	③．②のベクトルに対して直角なベクトルを算出する
			Vec3 normal = Vec3(-direction.y, direction.x, direction.z);

			if (j == 1)
			{
				// ベクトルu と ベクトルv を算出
				// ⑦．⑤のベクトルを180度回転する
				normal.x *= -1.0f;
				normal.y *= -1.0f;
				normal.z *= 1.0f;
			}

			//	④．③のベクトルを単位ベクトルにする
			float length = sqrtf(normal.x * normal.x + normal.y * normal.y+ normal.z * normal.z);
			normal.x /= length;
			normal.y /= length;
			normal.z /= length;

			// ⑤．線の幅 / 2 を④のベクトルに掛ける
			Vec3 new_pos = Vec3(
				direction.x + m_LineManager.m_Width / 2.0f * normal.x,
				direction.y + m_LineManager.m_Width / 2.0f * normal.y,
				direction.z + m_LineManager.m_Width / 2.0f * normal.z
			);

			// 	⑥．⑤のベクトルに座標を足した新しい座標を作る
			new_pos.x += m_LineManager.m_Line[i].m_Pos.x;
			new_pos.y += m_LineManager.m_Line[i].m_Pos.y;
			new_pos.z += m_LineManager.m_Line[i].m_Pos.z;

			// alpha 色の濃度
			float alpha = (float)m_LineManager.m_Line[i].m_Counter / 120.0f;
			t_LineDesc new_desc =
			{
				new_pos,

				// 比較	   // 真の場合:偽の場合
				// alphaが負の数の場合 0 を返す
				alpha > 0.0f ? alpha : 0.0f
			};

			desc_list.push_back(new_desc);
		}
	}

	if (dim_ == Dimendion::DIMENSION_2) { drawer2d.DrawLine(desc_list); }
	else if(dim_ == Dimendion::DIMENSION_3) { drawer3d.DrawLine(desc_list); };
}