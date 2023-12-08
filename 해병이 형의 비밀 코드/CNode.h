#pragma once

#include"CDefine.h"

#define DEPTH 1
#define TREESIZE 4


class CNode
{
public:

    CBox m_Box;
    CSphere m_Sphere;
    bool m_bIsLeaf = false;
    std::vector<TVector3> m_pCornerList;
    std::vector<DWORD>	m_CornerIndex;
    std::vector<CNode*> m_pChildList;
    std::vector<DWORD> m_vIndexList;
    std::vector <PNCT_VERTEX> m_vVertexList;
    ComPtr<ID3D11Buffer> m_pIndexBuffer = nullptr;
    ComPtr<ID3D11Buffer> m_pVertexBuffer = nullptr;
    int m_iCellRow;
    int m_iCellCol;


    int m_iDepth = 0;
    CNode* m_pParent = nullptr;
   
public:

    void SetParent(CNode* pParent);
    bool Release();
    bool CreateIndexBuffer();
    bool CreateVertexBuffer();
    bool Render();
    CNode();
    CNode(CNode* pParent, DWORD LT, DWORD RT, DWORD LB, DWORD RB);
    ~CNode()
    {
        m_pCornerList.clear();
        m_CornerIndex.clear();
        if (m_pChildList.size() != 0)
        {
            delete m_pChildList[0];
            delete m_pChildList[1];
            delete m_pChildList[2];
            delete m_pChildList[3];

        }
    }
  
  




};