#include "XFile.h"
#include <map>

bool XFile::Load(std::string file_name)
{
	// DirectX
	DxManager* Ins_DXManager = DxManager::GetInstance();

	if (!Ins_DXManager) { return false; }

	LPD3DXBUFFER p_material_buffer = NULL;
	
	// ���b�V���ǂݍ���
	if (FAILED(D3DXLoadMeshFromXA(
		file_name.c_str(),
		D3DXMESH_SYSTEMMEM,
		Ins_DXManager->GetStatus()->d3d_device,
		NULL,
		&p_material_buffer,
		NULL,
		&m_MaterialNum,
		&m_pMesh
	)))
	{
		return false;
	}

	m_pMeshMaterialList = new D3DMATERIAL9[m_MaterialNum];

	m_pTextureList = new LPDIRECT3DTEXTURE9[m_MaterialNum];

	D3DXMATERIAL* pmat_list = (D3DXMATERIAL*)p_material_buffer->GetBufferPointer();

	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		m_pMeshMaterialList[i] = pmat_list[i].MatD3D;
		m_pTextureList[i] = NULL;

		if(pmat_list[i].pTextureFilename != NULL)
		{
			std::string file_name = pmat_list[i].pTextureFilename;
			LPDIRECT3DTEXTURE9 texture = NULL;
			if(m_TextureList[file_name] == NULL)
			{
				D3DXCreateTextureFromFileA(Ins_DXManager->GetStatus()->d3d_device,
											file_name.c_str(),
											&m_TextureList[file_name]);
			}

			m_pTextureList[i] = m_TextureList[file_name];
			m_TextureNameList[i] = file_name;

		}
	}
	p_material_buffer->Release();

	return true;
}


XFile::~XFile()
{

	if(m_pMeshMaterialList != NULL)
	{
		delete[](m_pMeshMaterialList);
		m_pMeshMaterialList = NULL;
	}

	if (m_pTextureList != NULL) 
	{
		for(unsigned int i = 0; i < m_MaterialNum; i++)
		{
			if(m_pTextureList[i] != NULL &&
				m_TextureList[m_TextureNameList[i]] != NULL)
			{
				m_TextureList[m_TextureNameList[i]]->Release();
				m_pTextureList[i] = NULL;
			}
		}

		delete[](m_pTextureList);
		m_pTextureList = NULL;

	}

	m_TextureNameList.clear();
}

void XFile::Draw()
{
	DxManager* Ins_DXManager = DxManager::GetInstance();

	if (!Ins_DXManager) { return; }

	for(DWORD i = 0; i < m_MaterialNum; i++)
	{
		Ins_DXManager->GetStatus()->d3d_device->SetMaterial(&m_pMeshMaterialList[i]);

		Ins_DXManager->GetStatus()->d3d_device->SetTexture(0, m_pTextureList[i]);

		m_pMesh->DrawSubset(i);
	}

}