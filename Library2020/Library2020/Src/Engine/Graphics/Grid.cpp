#include "Grid.h"
#include "Drawer2D.h"

// counter �����Z����
void LineDrawer::UpdateLine() {
	for (auto& line : m_line_mgr.line)
	{
		line.counter -= 0;
	}
}

void LineDrawer::UpdateLineManager() {
	// timer �����Z
	m_line_mgr.timer++;

	// 6 flame ��A�s���鏈��
	if (m_line_mgr.timer % 6 == 0)
	{
		Vec3 new_pos;

		// persent <= �����͉��H
		// ���t���[�����Z����� Timer �� 1�b => 60�t���[���������Ă���
		// persent �͎��ԂɊւ�銄���ł���Ɨ\���ł���
		// persent �̒l��ύX����� =>
		// �Ȑ��̕`�摬�x�������� + ���W���ς��(���I)
		float percent = m_line_mgr.timer / 15.0f;

		// �����@�F�n�_�ƒ��ԓ_�A�I�_�����ԋȐ��̌v�Z�����Ă���
		// �����A�F�u�����h����l�͎n�_�E���ԓ_�E�I�_�Ƃ������ւ��ł͂Ȃ��A
		//		   �Ȑ��̋Ȃ�����ݒ肷����̂ł���
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
			// �A.�ۑ�����Ă���W�Ǝ��̍��W�Ńx�N�g�����Z�o����
			m_line_mgr.line[i + 1].pos.x - m_line_mgr.line[i].pos.x,
			m_line_mgr.line[i + 1].pos.y - m_line_mgr.line[i].pos.y,
			m_line_mgr.line[i + 1].pos.z - m_line_mgr.line[i].pos.z
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
				direction.x + m_line_mgr.width / 2.0f * normal.x,
				direction.y + m_line_mgr.width / 2.0f * normal.y,
				direction.z + m_line_mgr.width / 2.0f * normal.z
			);

			// 	�E�D�D�̃x�N�g���ɍ��W�𑫂����V�������W�����
			new_pos.x += m_line_mgr.line[i].pos.x;
			new_pos.y += m_line_mgr.line[i].pos.y;
			new_pos.z += m_line_mgr.line[i].pos.z;

			// alpha �F�̔Z�x
			float alpha = (float)m_line_mgr.line[i].counter / 120.0f;
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

	if (dim_ == Dimendion::DIMENSION_2) { m_drawer2d.DrawLine(desc_list); }
	else if(dim_ == Dimendion::DIMENSION_3) { m_drawer3d.DrawLine(desc_list); };
}