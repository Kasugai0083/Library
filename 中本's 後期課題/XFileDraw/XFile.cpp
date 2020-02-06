#include "XFile.h"
#include <map>

extern std::map<std::string, LPDIRECT3DTEXTURE9> g_xFileTextureList;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;
std::map<std::string, XFile *>g_pXFileList;	// �ǂݍ���XFile�̃��X�g

/*
	XFile�ǂݍ���
		�߂�l�F
			�ǂݍ��݌��ʁF
				�����F
					true
					true
				���s�F
					false
		�����F
			std::string file_name�F
				�t�@�C����
		���e�F
			XFile�̓ǂݍ��݂��s��
*/
bool XFile::Load(std::string file_name)
{
	// XFile�f�[�^���i�[���鉼�o�b�t�@
	LPD3DXBUFFER p_material_buffer = NULL;

	// �@�DXFile�̓ǂݍ��� start
	if (FAILED(D3DXLoadMeshFromXA(
		// �t�@�C����
		file_name.c_str(),
		// �V�X�e��
		D3DXMESH_SYSTEMMEM,
		// graphics�f�o�C�X
		g_pD3DDevice,
		// NULL
		nullptr,
		// �}�e���A���i�[�p�o�b�t�@
		&p_material_buffer,
		// NULL
		nullptr,
		// �}�e���A���̐�
		&m_MaterialNum,
		// ���b�V���f�[�^
		&m_pMesh) ) )
	{
		return false;
	}
	// �@�DXFile�̓ǂݍ��� end

		//X�t�@�C���ɖ@�����Ȃ��ꍇ�́A�@������������
	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL)) {

		ID3DXMesh* pTempMesh = NULL;

		m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(),
			m_pMesh->GetFVF() | D3DFVF_NORMAL, g_pD3DDevice, &pTempMesh);

		D3DXComputeNormals(pTempMesh, NULL);
		m_pMesh->Release();
		m_pMesh = pTempMesh;
	}

	// �A.�}�e���A�����̃R�s�[ start
	// �ǂݍ��܂ꂽXFile�̃}�e���A������D3DMATERIAL9��p�ӂ���
	m_pMeshMaterialList = new D3DMATERIAL9[m_MaterialNum];

	// ���b�V���Ɏg�p����Ă���e�N�X�`���p�̔z���p�ӂ���
	m_pTextureList = new LPDIRECT3DTEXTURE9[m_MaterialNum];

	// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	D3DXMATERIAL *pmat_list = (D3DXMATERIAL*)p_material_buffer->GetBufferPointer();

	// �e���b�V���̃}�e���A�������擾����
	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		// �}�e���A���擾
		m_pMeshMaterialList[i] = pmat_list[i].MatD3D;
		m_pTextureList[i] = NULL;

		// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
		if (pmat_list[i].pTextureFilename != NULL)
		{
			std::string file_name = pmat_list[i].pTextureFilename;
			LPDIRECT3DTEXTURE9 texture = NULL;
			if (g_xFileTextureList[file_name] == NULL)
			{
				D3DXCreateTextureFromFileA(g_pD3DDevice,
											file_name.c_str(),
											&g_xFileTextureList[file_name]);
			}

			m_pTextureList[i] = g_xFileTextureList[file_name];
			m_TextureNameList[i] = file_name;
		}
	}

	// �}�e���A���̃R�s�[���I������̂Ńo�b�t�@���������
	p_material_buffer->Release();
	// �A.�}�e���A�����̃R�s�[ end

	return true;
}

XFile::~XFile(void)
{
	// �}�e���A�����X�g�̉��
	if (m_pMeshMaterialList != NULL)
	{
		delete[] (m_pMeshMaterialList);
		m_pMeshMaterialList = NULL;
	}

	// �e�N�X�`�����X�g�̉��
	if (m_pTextureList != NULL)
	{
		for (int i = 0; i < m_MaterialNum; i++)
		{
			if (m_pTextureList[i] != NULL &&
				g_xFileTextureList[m_TextureNameList[i]] != NULL)
			{
				// �e�N�X�`���̉��
				g_xFileTextureList[m_TextureNameList[i]]->Release();
				m_pTextureList[i] = NULL;
			}
		}

		delete[] (m_pTextureList);
		m_pTextureList = NULL;
	}

	// �e�N�X�`���t�@�C�������X�g�̏�����
	m_TextureNameList.clear();
}

void XFile::Draw(void)
{
	// XFile�`�掞�̂݃f�v�X�o�b�t�@��ON�ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->LightEnable(0, false);

	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		// �}�e���A���̐ݒ�
		g_pD3DDevice->SetMaterial(&m_pMeshMaterialList[i]);
		// �e�N�X�`���̐ݒ�
		g_pD3DDevice->SetTexture(0, m_pTextureList[i]);
		// ���b�V����`��
		m_pMesh->DrawSubset(i);
	}

	// �}�e���A���̐ݒ�͎���SetMaterial�܂ň����p�����
}


void XFile::Update()
{
}