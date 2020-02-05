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
		new_pos.X = 
			(1 - percent) 
			* (1 - percent) 
			* m_LineManager.m_Start.X + 2 
			* (1 - percent) 
			* percent 
			* m_LineManager.m_Center.X + percent 
			* percent 
			* m_LineManager.m_End.X;

		new_pos.Y = 
			(1 - percent) 
			* (1 - percent) 
			* m_LineManager.m_Start.Y + 2 
			* (1 - percent) * percent 
			* m_LineManager.m_Center.Y + percent 
			* percent 
			* m_LineManager.m_End.Y;

		new_pos.Z = 
			(1 - percent) 
			* (1 - percent) 
			* m_LineManager.m_Start.Z + 2 
			* (1 - percent) * percent 
			* m_LineManager.m_Center.Z + percent 
			* percent 
			* m_LineManager.m_End.Z;

		Line new_line =
		{
			new_pos,
			120,
		};
		m_LineManager.m_Line.push_back(new_line);
	}

	UpdateLine();
}

void LineDrawer::DrawLine() {
	if (m_LineManager.m_Line.size() <= 2)
	{
		return;
	}

	std::vector<LineDesc> desc_list;

	for (int i = 0; i < (int)m_LineManager.m_Line.size() - 1; i++)
	{
		Vec3 direction = Vec3(
			// �A.�ۑ�����Ă���W�Ǝ��̍��W�Ńx�N�g�����Z�o����
			m_LineManager.m_Line[i + 1].m_Pos.X - m_LineManager.m_Line[i].m_Pos.X,
			m_LineManager.m_Line[i + 1].m_Pos.Y - m_LineManager.m_Line[i].m_Pos.Y,
			m_LineManager.m_Line[i + 1].m_Pos.Z - m_LineManager.m_Line[i].m_Pos.Z
		);


		// �G�D�F�̃x�N�g���ƍ��W�𑫂����V�������W�����
		for (int j = 0; j < 2; j++)
		{
			// 	�B�D�A�̃x�N�g���ɑ΂��Ē��p�ȃx�N�g�����Z�o����
			Vec3 normal = Vec3(-direction.Y, direction.X, direction.Z);

			if (j == 1)
			{
				// �x�N�g��u �� �x�N�g��v ���Z�o
				// �F�D�D�̃x�N�g����180�x��]����
				normal.X *= -1.0f;
				normal.Y *= -1.0f;
				normal.Z *= 1.0f;
			}

			//	�C�D�B�̃x�N�g����P�ʃx�N�g���ɂ���
			float length = sqrtf(normal.X * normal.X + normal.Y * normal.Y+ normal.Z * normal.Z);
			normal.X /= length;
			normal.Y /= length;
			normal.Z /= length;

			// �D�D���̕� / 2 ���C�̃x�N�g���Ɋ|����
			Vec3 new_pos = Vec3(
				direction.X + m_LineManager.m_Width / 2.0f * normal.X,
				direction.Y + m_LineManager.m_Width / 2.0f * normal.Y,
				direction.Z + m_LineManager.m_Width / 2.0f * normal.Z
			);

			// 	�E�D�D�̃x�N�g���ɍ��W�𑫂����V�������W�����
			new_pos.X += m_LineManager.m_Line[i].m_Pos.X;
			new_pos.Y += m_LineManager.m_Line[i].m_Pos.Y;
			new_pos.Z += m_LineManager.m_Line[i].m_Pos.Z;

			// alpha �F�̔Z�x
			float alpha = (float)m_LineManager.m_Line[i].m_Counter / 120.0f;
			LineDesc new_desc =
			{
				new_pos,

				// ��r	   // �^�̏ꍇ:�U�̏ꍇ
				// alpha�����̐��̏ꍇ 0 ��Ԃ�
				alpha > 0.0f ? alpha : 0.0f
			};

			desc_list.push_back(new_desc);
		}
	}

	m_Drawer.DrawLine(desc_list);

}