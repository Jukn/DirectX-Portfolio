#include "CMap.h"
#include"CoreInterface.h"
#include"CTextureMgr.h"
#include"CShaderMgr.h"

bool CMap::Load(CMapDesc& MapDesc)
{
	if (!CreateMap(MapDesc))
	{
		return false;
	}

	return true;
}



bool CMap::GenerateVertexNormal()
{
	InitFaceNormal();
	GenNormalLookupTable();
	CalcPerVertexNormalsFastLookup();

	return true;
}

void CMap::CalcVertexColor(TVector3 vLightDir)
{
	for (int iRow = 0; iRow < m_iRow; iRow++)
	{
		for (int iCol = 0; iCol < m_iCol; iCol++)
		{

			int  iVertexIndex = iRow * m_iCol + iCol;
			
			float fDot = D3DXVec3Dot(&vLightDir, &m_vVertexList[iVertexIndex].Nor);
			
			m_vVertexList[iVertexIndex].Col *= fDot;
			m_vVertexList[iVertexIndex].Col.w = 1.0f;
		}
	}
}

void CMap::InitFaceNormal()
{
	m_pFaceNormals = new TVector3[m_iNumFace];

	for (int i = 0; i < m_iNumFace; ++i)
	{

		m_pFaceNormals[i] = TVector3(0.0f, 0.0f, 0.0f);
	}

}
void CMap::GenNormalLookupTable()
{
	// We're going to create a table that lists, for each vertex, the
	// triangles which that vertex is a part of.

	if (m_pNormalLookupTable != NULL)
	{
		free(m_pNormalLookupTable);
		m_pNormalLookupTable = NULL;
	}

	// Each vertex may be a part of up to 6 triangles in the grid, so
	// create a buffer to hold a pointer to the normal of each neighbor.
	int buffersize = m_iRow * m_iCol * 6;

	m_pNormalLookupTable = (int*)malloc(sizeof(void*) * buffersize);
	for (int i = 0; i < buffersize; i++)
		m_pNormalLookupTable[i] = -1;

	// Now that the table is initialized, populate it with the triangle data.

	// For each triangle
	//   For each vertex in that triangle
	//     Append the triangle number to lookuptable[vertex]
	for (int i = 0; i < m_iNumFace; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Find the next empty slot in the vertex's lookup table "slot"
			for (int k = 0; k < 6; k++)
			{
				int vertex = m_vIndexList[i * 3 + j];
				if (m_pNormalLookupTable[vertex * 6 + k] == -1)
				{
					m_pNormalLookupTable[vertex * 6 + k] = i;
					break;
				}
			}
		}  // For each vertex that is part of the current triangle
	} // For each triangle
}

TVector3 CMap::ComputeFaceNormal(DWORD dwIndex0, DWORD dwIndex1, DWORD dwIndex2)
{
	TVector3 vNormal;
	TVector3 v0 = m_vVertexList[dwIndex1].Pos - m_vVertexList[dwIndex0].Pos;
	TVector3 v1 = m_vVertexList[dwIndex2].Pos - m_vVertexList[dwIndex0].Pos;

	D3DXVec3Cross(&vNormal,&v0,&v1);
	vNormal.Normalize();
	

	return vNormal;
}

void CMap::CalcFaceNormals()
{
	// Loop over how many faces there are
	int j = 0;
	for (int i = 0; i < m_iNumFace * 3; i += 3)
	{
		DWORD i0 = m_vIndexList[i];
		DWORD i1 = m_vIndexList[i + 1];
		DWORD i2 = m_vIndexList[i + 2];
		m_pFaceNormals[j] = ComputeFaceNormal(i0, i1, i2);
		j++;
	}
}

void CMap::CalcPerVertexNormalsFastLookup()
{
	// First, calculate the face normals for each triangle.
	CalcFaceNormals();

	// For each vertex, sum the normals indexed by the normal lookup table.
	int j = 0;
	for (int i = 0; i < m_iVertices; i++)
	{
		TVector3 avgNormal;
		avgNormal = TVector3(0.0f, 0.0f, 0.0f);

		// Find all the triangles that this vertex is a part of.
		for (j = 0; j < 6; j++)
		{
			int triIndex;
			triIndex = m_pNormalLookupTable[i * 6 + j];

			// If the triangle index is valid, get the normal and average it in.
			if (triIndex != -1)
			{
				avgNormal += m_pFaceNormals[triIndex];
			}
			else
				break;
		}

		// Complete the averaging step by dividing & normalizing.
		_ASSERT(j > 0);
		avgNormal.x /= (float)j;//.DivConst( (float)(j) );
		avgNormal.y /= (float)j;
		avgNormal.z /= (float)j;
		avgNormal.Normalize();

		// Set the vertex normal to this new normal.
		m_vVertexList[i].Nor.x = avgNormal.x;
		m_vVertexList[i].Nor.y = avgNormal.y;
		m_vVertexList[i].Nor.z = avgNormal.z;

	}  // For each vertex

	/////////////////////////////////////////////////////////////////
	// 페이스 노말 계산 및  이웃 페이스 인덱스 저장하여 정점 노말 계산
	/////////////////////////////////////////////////////////////////	
	if (m_bStaticLight) CalcVertexColor(m_vLightDir);
}

float CMap::GetHeightVertex(UINT index)
{
	return 0.0f;
}
TVector3 CMap::GetNormalVertex(UINT index)
{
	return TVector3(0.0f, 1.0f, 0.0f);
}
TVector4 CMap::GetColorVertex(UINT index)
{
	return TVector4(1.0f, 1.0f, 1.0f, 1.0f);
}
TVector2 GetTextureVertex(float offsetX, float offsetY)
{
	return TVector2(offsetX, offsetY);
}





bool CMap::CreateMap(CMapDesc& MapDesc)
{
	/*if (MapDesc.iCol > 1025 || MapDesc.iRow > 1025)
	{
		MapDesc.iCol = 1025;
		MapDesc.iRow = 1025;
	}*/
	
	m_iRow = MapDesc.iRow;
	m_iCol = MapDesc.iCol;
	m_iCellRow = MapDesc.iRow - 1;
	m_iCellCol = MapDesc.iCol - 1;
	m_iVertices = m_iRow * m_iCol;
	m_iNumFace = m_iCellRow * m_iCellCol * 2;
	m_fCellDistance = MapDesc.fCellDistance;
	m_MapDesc = MapDesc;
	CObject::Create(m_MapDesc.szTextureName.c_str(), m_MapDesc.szShaderName.c_str());




	return true;
}



bool CMap::CreateVertexData()
{
	m_vVertexList.resize(m_iVertices);

	//float fHalfCols = (m_iCol - 1) / 2.0f;
	//float fHalfRows = (m_iRow - 1) / 2.0f;
	//
	//
	//
	//
	//for (int Row = 0; Row < m_iRow; ++Row)
	//{
	//	for (int Col = 0; Col < m_iCol; ++Col)
	//	{
	//		int VertexIndex = Row * m_iCol + Col;
	//		m_vVertexList[VertexIndex].Pos.x = (Col - fHalfCols) * m_fCellDistance;
	//		m_vVertexList[VertexIndex].Pos.z = -((Row - fHalfRows) * m_fCellDistance);
	//		m_vVertexList[VertexIndex].Pos.y = GetHeightVertex(VertexIndex);
	//		
	//		m_vVertexList[VertexIndex].Nor= GetNormalVertex(VertexIndex);
	//		m_vVertexList[VertexIndex].Col= GetColorVertex(VertexIndex);
	//		m_vVertexList[VertexIndex].Tex = GetTextureVertex(fOffSetU*Col , fOffSetV*Row);
	//
	//	}
	//}
	float fOffSetU = 1.0f / (m_iCol - 1);
	float fOffSetV = 1.0f / (m_iRow - 1);
	float fHalfCols = (m_iCol - 1) * 0.5f;
	float fHalfRows = (m_iRow - 1) * 0.5f;
	m_iCellRow = (m_iRow - 1);
	m_iCellCol = (m_iCol - 1);
	m_iNumFace = m_iCellRow * m_iCellCol * 2;

	for (int iRow = 0; iRow < m_iRow; iRow++)
	{
		for (int iCol = 0; iCol < m_iCol; iCol++)
		{
			int  iVertexIndex = iRow * m_iCol + iCol;
			m_vVertexList[iVertexIndex].Pos.x = (iCol - fHalfCols) * m_fCellDistance;
			m_vVertexList[iVertexIndex].Pos.z = -((iRow - fHalfRows) * m_fCellDistance);
			m_vVertexList[iVertexIndex].Pos.y = GetHeightVertex(iVertexIndex)*1;
			m_vVertexList[iVertexIndex].Nor = GetNormalVertex(iVertexIndex);
			m_vVertexList[iVertexIndex].Col = GetColorVertex(iVertexIndex);
			m_vVertexList[iVertexIndex].Tex = GetTextureVertex(fOffSetU * iCol, fOffSetV * iRow);

		}
	}

	return true;
}

bool CMap::CreateIndexData()
{
	m_vIndexList.resize(m_iNumFace * 3);

	int CurIndex = 0;
	for (int Row = 0; Row < m_iCellRow; ++Row)
	{

		for (int Col = 0; Col < m_iCellCol; ++Col)
		{

			int NextRow = Row + 1;
			int NextCol = Col + 1;

			m_vIndexList[CurIndex + 0] = Row * m_iCol + Col;
			m_vIndexList[CurIndex + 1] = Row * m_iCol + NextCol;
			m_vIndexList[CurIndex + 2] = NextRow * m_iCol + Col;
			m_vIndexList[CurIndex + 3] = m_vIndexList[CurIndex + 2];
			m_vIndexList[CurIndex + 4] = m_vIndexList[CurIndex + 1];
			m_vIndexList[CurIndex + 5] = NextRow * m_iCol + NextCol;

			CurIndex += 6;

		}
	}
	
	GenerateVertexNormal();

	return true;
}
bool CMap::Init()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	return true;
}

bool CMap::Frame()
{
	return true;
}



bool CMap::Release()
{

	if (m_pNormalLookupTable)
	{
		free(m_pNormalLookupTable);
		m_pNormalLookupTable = NULL;
	}
	if (m_pFaceNormals != NULL)
	{
		delete m_pFaceNormals;
		m_pFaceNormals = NULL;
	}

	return true;
}
CMap::CMap(void)
{
	m_iNumFace = 0;
	
	m_iCol = 0;
	m_iRow = 0;
	m_vLightDir = { 0,1,0 };
	m_pNormalLookupTable = nullptr;
	m_pFaceNormals = nullptr;
	
	
}
