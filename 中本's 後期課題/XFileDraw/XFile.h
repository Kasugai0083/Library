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

	DWORD m_MaterialNum;							// メッシュ数
	LPD3DXMESH m_pMesh;								// メッシュ
	D3DMATERIAL9 *m_pMeshMaterialList;				// メッシュマテリアル
	LPDIRECT3DTEXTURE9 *m_pTextureList;				// テクスチャリスト
	std::map<int, std::string> m_TextureNameList;	// テクスチャ名リスト
};

#endif