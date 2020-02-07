#include "Grid.h"
#include "Drawer2D.h"

// m_Counter �����Z����
void LineDrawer::UpdateLine() {
	for (auto& line : m_LineManager.m_Line)
	{
		line.m_Counter -= 0;
	}
}

void LineDrawer::UpdateLineManager() {
	// m_Timer �����Z
	m_LineManager.m_Timer++;

	// 6 flame ��A�s���鏈��
	if (m_LineManager.m_Timer % 6 == 0)
	{
		Vec3 new_pos;

		// persent <= �����͉��H
		// ���t���[�����Z����� Timer �� 1�b => 60�t���[���������Ă���
		// persent �͎��ԂɊւ�銄���ł���Ɨ\���ł���
		// persent �̒l��ύX����� =>
		// �Ȑ��̕`�摬�x�������� + ���W���ς��(���I)
		float percent = m_LineManager.m_Timer / 15.0f;

		// �����@�F�n�_�ƒ��ԓ_�A�I�_�����ԋȐ��̌v�Z�����Ă���
		// �����A�F�u�����h����l�͎n�_�E���ԓ_�E�I�_�Ƃ������ւ��ł͂Ȃ��A
		//		   �Ȑ��̋Ȃ�����ݒ肷����̂ł���
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
			// �A.�ۑ�����Ă���W�Ǝ��̍��W�Ńx�N�g�����Z�o����
			m_LineManager.m_Line[i + 1].m_Pos.x - m_LineManager.m_Line[i].m_Pos.x,
			m_LineManager.m_Line[i + 1].m_Pos.y - m_LineManager.m_Line[i].m_Pos.y,
			m_LineManager.m_Line[i + 1].m_Pos.z - m_LineManager.m_Line[i].m_Pos.z
		);


		// �G�D�F�̃x�N�g���ƍ��W�𑫂����V�������W�����
		for (int j = 0; j < 2; j++)
		{
			// 	�B�D�A�̃x�N�g���ɑ΂��Ē��p�ȃx�N�g�����Z�o����
			Vec3 normal = Vec3(-direction.y, direction.x, direction.z);

			if (j == 1)
			{
				// �x�N�g��u �� �x�N�g��v ���Z�o
				// �F�D�D�̃x�N�g����180�x��]����
				normal.x *= -1.0f;
				normal.y *= -1.0f;
				normal.z *= 1.0f;
			}

			//	�C�D�B�̃x�N�g����P�ʃx�N�g���ɂ���
			float length = sqrtf(normal.x * normal.x + normal.y * normal.y+ normal.z * normal.z);
			normal.x /= length;
			normal.y /= length;
			normal.z /= length;

			// �D�D���̕� / 2 ���C�̃x�N�g���Ɋ|����
			Vec3 new_pos = Vec3(
				direction.x + m_LineManager.m_Width / 2.0f * normal.x,
				direction.y + m_LineManager.m_Width / 2.0f * normal.y,
				direction.z + m_LineManager.m_Width / 2.0f * normal.z
			);

			// 	�E�D�D�̃x�N�g���ɍ��W�𑫂����V�������W�����
			new_pos.x += m_LineManager.m_Line[i].m_Pos.x;
			new_pos.y += m_LineManager.m_Line[i].m_Pos.y;
			new_pos.z += m_LineManager.m_Line[i].m_Pos.z;

			// alpha �F�̔Z�x
			float alpha = (float)m_LineManager.m_Line[i].m_Counter / 120.0f;
			t_LineDesc new_desc =
			{
				new_pos,

				// ��r	   // �^�̏ꍇ:�U�̏ꍇ
				// alpha�����̐��̏ꍇ 0 ��Ԃ�
				alpha > 0.0f ? alpha : 0.0f
			};

			desc_list.push_back(new_desc);
		}
	}

	if (dim_ == Dimendion::DIMENSION_2) { drawer2d.DrawLine(desc_list); }
	else if(dim_ == Dimendion::DIMENSION_3) { drawer3d.DrawLine(desc_list); };
}