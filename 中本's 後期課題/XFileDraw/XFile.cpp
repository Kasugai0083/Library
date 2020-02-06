#include "XFile.h"
#include <map>

extern std::map<std::string, LPDIRECT3DTEXTURE9> g_xFileTextureList;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;
std::map<std::string, XFile *>g_pXFileList;	// 読み込んだXFileのリスト

/*
	XFile読み込み
		戻り値：
			読み込み結果：
				成功：
					true
					true
				失敗：
					false
		引数：
			std::string file_name：
				ファイル名
		内容：
			XFileの読み込みを行う
*/
bool XFile::Load(std::string file_name)
{
	// XFileデータを格納する仮バッファ
	LPD3DXBUFFER p_material_buffer = NULL;

	// ①．XFileの読み込み start
	if (FAILED(D3DXLoadMeshFromXA(
		// ファイル名
		file_name.c_str(),
		// システム
		D3DXMESH_SYSTEMMEM,
		// graphicsデバイス
		g_pD3DDevice,
		// NULL
		nullptr,
		// マテリアル格納用バッファ
		&p_material_buffer,
		// NULL
		nullptr,
		// マテリアルの数
		&m_MaterialNum,
		// メッシュデータ
		&m_pMesh) ) )
	{
		return false;
	}
	// ①．XFileの読み込み end

		//Xファイルに法線がない場合は、法線を書き込む
	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL)) {

		ID3DXMesh* pTempMesh = NULL;

		m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(),
			m_pMesh->GetFVF() | D3DFVF_NORMAL, g_pD3DDevice, &pTempMesh);

		D3DXComputeNormals(pTempMesh, NULL);
		m_pMesh->Release();
		m_pMesh = pTempMesh;
	}

	// ②.マテリアル情報のコピー start
	// 読み込まれたXFileのマテリアル分のD3DMATERIAL9を用意する
	m_pMeshMaterialList = new D3DMATERIAL9[m_MaterialNum];

	// メッシュに使用されているテクスチャ用の配列を用意する
	m_pTextureList = new LPDIRECT3DTEXTURE9[m_MaterialNum];

	// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
	D3DXMATERIAL *pmat_list = (D3DXMATERIAL*)p_material_buffer->GetBufferPointer();

	// 各メッシュのマテリアル情報を取得する
	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		// マテリアル取得
		m_pMeshMaterialList[i] = pmat_list[i].MatD3D;
		m_pTextureList[i] = NULL;

		// マテリアルで設定されているテクスチャ読み込み
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

	// マテリアルのコピーが終わったのでバッファを解放する
	p_material_buffer->Release();
	// ②.マテリアル情報のコピー end

	return true;
}

XFile::~XFile(void)
{
	// マテリアルリストの解放
	if (m_pMeshMaterialList != NULL)
	{
		delete[] (m_pMeshMaterialList);
		m_pMeshMaterialList = NULL;
	}

	// テクスチャリストの解放
	if (m_pTextureList != NULL)
	{
		for (int i = 0; i < m_MaterialNum; i++)
		{
			if (m_pTextureList[i] != NULL &&
				g_xFileTextureList[m_TextureNameList[i]] != NULL)
			{
				// テクスチャの解放
				g_xFileTextureList[m_TextureNameList[i]]->Release();
				m_pTextureList[i] = NULL;
			}
		}

		delete[] (m_pTextureList);
		m_pTextureList = NULL;
	}

	// テクスチャファイル名リストの初期化
	m_TextureNameList.clear();
}

void XFile::Draw(void)
{
	// XFile描画時のみデプスバッファをONにする
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->LightEnable(0, false);

	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		// マテリアルの設定
		g_pD3DDevice->SetMaterial(&m_pMeshMaterialList[i]);
		// テクスチャの設定
		g_pD3DDevice->SetTexture(0, m_pTextureList[i]);
		// メッシュを描画
		m_pMesh->DrawSubset(i);
	}

	// マテリアルの設定は次のSetMaterialまで引き継がれる
}


void XFile::Update()
{
}