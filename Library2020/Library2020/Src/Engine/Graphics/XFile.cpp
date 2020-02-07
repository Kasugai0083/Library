#include "XFile.h"
#include <map>

bool XFile::Load(std::string file_name)
{
	// DirectX
	DxManager* mgr = DxManager::GetInstance();

	if (!mgr) { return false; }

	LPD3DXBUFFER p_material_buffer = NULL;
	
	// ƒƒbƒVƒ…“Ç‚Ýž‚Ý
	if (FAILED(D3DXLoadMeshFromXA(
		file_name.c_str(),
		D3DXMESH_SYSTEMMEM,
		mgr->GetStatus()->d3d_device,
		NULL,
		&p_material_buffer,
		NULL,
		&m_material_num,
		&m_mesh
	)))
	{
		return false;
	}

	m_mesh_material_list = new D3DMATERIAL9[m_material_num];

	m_ptr_tex_list = new LPDIRECT3DTEXTURE9[m_material_num];

	D3DXMATERIAL* pmat_list = (D3DXMATERIAL*)p_material_buffer->GetBufferPointer();

	for (DWORD i = 0; i < m_material_num; i++)
	{
		m_mesh_material_list[i] = pmat_list[i].MatD3D;
		m_ptr_tex_list[i] = NULL;

		if(pmat_list[i].pTextureFilename != NULL)
		{
			std::string file_name = pmat_list[i].pTextureFilename;
			LPDIRECT3DTEXTURE9 texture = NULL;
			if(m_tex_list[file_name] == NULL)
			{
				D3DXCreateTextureFromFileA(mgr->GetStatus()->d3d_device,
											file_name.c_str(),
											&m_tex_list[file_name]);
			}

			m_ptr_tex_list[i] = m_tex_list[file_name];
			m_tex_name_list[i] = file_name;

		}
	}
	p_material_buffer->Release();

	return true;
}


XFile::~XFile()
{

	if(m_mesh_material_list != NULL)
	{
		delete[](m_mesh_material_list);
		m_mesh_material_list = NULL;
	}

	if (m_ptr_tex_list != NULL) 
	{
		for(unsigned int i = 0; i < m_material_num; i++)
		{
			if(m_ptr_tex_list[i] != NULL &&
				m_tex_list[m_tex_name_list[i]] != NULL)
			{
				m_tex_list[m_tex_name_list[i]]->Release();
				m_ptr_tex_list[i] = NULL;
			}
		}

		delete[](m_ptr_tex_list);
		m_ptr_tex_list = NULL;

	}

	m_tex_name_list.clear();
}

void XFile::Draw()
{
	DxManager* mgr = DxManager::GetInstance();

	if (!mgr) { return; }

	for(DWORD i = 0; i < m_material_num; i++)
	{
		mgr->GetStatus()->d3d_device->SetMaterial(&m_mesh_material_list[i]);

		mgr->GetStatus()->d3d_device->SetTexture(0, m_ptr_tex_list[i]);

		m_mesh->DrawSubset(i);
	}

}