#include "Grid.h"
#include "Drawer2D.h"

// counter を減算する
void LineDrawer::UpdateLine() {
	for (auto& line : m_line_mgr.line)
	{
		line.counter -= 0;
	}
}

void LineDrawer::UpdateLineManager() {
	// timer を加算
	m_line_mgr.timer++;

	// 6 flame 後、行われる処理
	if (m_line_mgr.timer % 6 == 0)
	{
		Vec3 new_pos;

		// persent <= こいつは何？
		// 毎フレーム加算される Timer に 1秒 => 60フレームが割られている
		// persent は時間に関わる割合であると予測できる
		// persent の値を変更すると =>
		// 曲線の描画速度があがる + 座標が変わる(問題！)
		float percent = m_line_mgr.timer / 15.0f;

		// 仮説①：始点と中間点、終点を結ぶ曲線の計算をしている
		// 仮説②：ブレンドする値は始点・中間点・終点といった関わりではなく、
		//		   曲線の曲がり具合を設定するものである
		new_pos.x = 
			(1 - percent) 
			* (1 - percent) 
			* m_line_mgr.start.x + 2 
			* (1 - percent) 
			* percent 
			* m_line_mgr.center.x + percent 
			* percent 
			* m_line_mgr.end.x;

		new_pos.y = 
			(1 - percent) 
			* (1 - percent) 
			* m_line_mgr.start.y + 2 
			* (1 - percent) * percent 
			* m_line_mgr.center.y + percent 
			* percent 
			* m_line_mgr.end.y;

		new_pos.z = 
			(1 - percent) 
			* (1 - percent) 
			* m_line_mgr.start.z + 2 
			* (1 - percent) * percent 
			* m_line_mgr.center.z + percent 
			* percent 
			* m_line_mgr.end.z;

		t_Line new_line =
		{
			new_pos,
			120,
		};
		m_line_mgr.line.push_back(new_line);
	}

	UpdateLine();
}

void LineDrawer::DrawLine(Dimendion dim_) {
	if (m_line_mgr.line.size() <= 2)
	{
		return;
	}

	std::vector<t_LineDesc> desc_list;

	for (int i = 0; i < (int)m_line_mgr.line.size() - 1; i++)
	{
		Vec3 direction = Vec3(
			// ②.保存されてる座標と次の座標でベクトルを算出する
			m_line_mgr.line[i + 1].pos.x - m_line_mgr.line[i].pos.x,
			m_line_mgr.line[i + 1].pos.y - m_line_mgr.line[i].pos.y,
			m_line_mgr.line[i + 1].pos.z - m_line_mgr.line[i].pos.z
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
				direction.x + m_line_mgr.width / 2.0f * normal.x,
				direction.y + m_line_mgr.width / 2.0f * normal.y,
				direction.z + m_line_mgr.width / 2.0f * normal.z
			);

			// 	⑥．⑤のベクトルに座標を足した新しい座標を作る
			new_pos.x += m_line_mgr.line[i].pos.x;
			new_pos.y += m_line_mgr.line[i].pos.y;
			new_pos.z += m_line_mgr.line[i].pos.z;

			// alpha 色の濃度
			float alpha = (float)m_line_mgr.line[i].counter / 120.0f;
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

	if (dim_ == Dimendion::DIMENSION_2) { m_drawer2d.DrawLine(desc_list); }
	else if(dim_ == Dimendion::DIMENSION_3) { m_drawer3d.DrawLine(desc_list); };
}