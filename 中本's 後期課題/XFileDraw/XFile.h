#ifndef XFILE_H_
#define XFILE_H_

#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

class XFile
{
public:
	XFile() :
		m_MaterialNum(0),
		m_pMesh(NULL),
		m_pMeshMaterialList(NULL),
		m_pTextureList(NULL)
	{
		m_X = 0.0f;
		m_Y = 0.0f;
		m_Z = 0.0f;
	}
	~XFile(void);
	bool Load(std::string file_name);
	void Draw(void);

	void Update();
private:
	float m_X, m_Y, m_Z;
	float m_Scale;

	DWORD m_MaterialNum;							// ���b�V����
	LPD3DXMESH m_pMesh;								// ���b�V��
	D3DMATERIAL9 *m_pMeshMaterialList;				// ���b�V���}�e���A��
	LPDIRECT3DTEXTURE9 *m_pTextureList;				// �e�N�X�`�����X�g
	std::map<int, std::string> m_TextureNameList;	// �e�N�X�`�������X�g
};

#endif