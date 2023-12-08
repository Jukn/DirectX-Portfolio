#pragma once
#include"CNode.h"
#include<set>
#include<queue>
#include"CHeightMap.h"
#include"CObject.h"

class CQuadTree
{
public:
	std::queue<CNode*> m_pQueue;
	CNode* m_pRootNode;
	int m_iMaxDepthLimit =2;
	int m_iMaxDepth;
	int m_iMinSplitDistance = 2;
	int m_fMinDivideSize=1;
	bool m_bUsedIndexList = false;
	DWORD m_Width;
	DWORD m_Height;
	CMap* m_pMap;
	std::vector<PNCT_VERTEX> m_vVertexList;
	std::vector<DWORD> m_vTreeIndexList;
	std::vector<CNode*>DrawNodeList;

	std::vector<shared_ptr<CObject>> TestBoxlist;

public:
	void BuildQuadTree(CMap* pMap , DWORD Width , DWORD Height, std::vector<PNCT_VERTEX> vVertexList);
	void CreateBoundingBox(CNode* pNode);
	TVector2 GetHeightFromNode(DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR);
	TVector2 GetHeightFromNode(CNode* pnode);
	bool CreateIndexBuffer();
	bool SubDivide(CNode* pNode);
	void LevelOrder(CNode* pNode);
	void PostOrder(CNode* pNode);
	void PreOrder(CNode* pNode, CPlane* plane);
	void BuildTree(CNode* pNode);
	CNode* GetRootNode();
	CNode* CreateNode(CNode* pParent, DWORD LT, DWORD RT, DWORD LB, DWORD RB);
	bool UpdateVertexList(CNode* pNode);
	//bool CreateIndexBuffer(CNode* pNode);*/
	DWORD CheckSize(DWORD dwSize);

	void FindDrawNode(CNode* pNode);


	void DebugBox(CBox box, CSphere sphere);
public:
	bool Init();
	bool PreFrame();
	bool Frame();
	bool PostFrame();
	bool Render(CPlane* plane);
	bool Release();

	


public:


	~CQuadTree()
	{
		
		
	}



};

