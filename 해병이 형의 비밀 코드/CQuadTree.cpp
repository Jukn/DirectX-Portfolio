#include "CQuadTree.h"
#include"CCollision.h"

void CQuadTree::BuildTree(CNode* pNode)
{
   

    if (SubDivide(pNode))
    {
        for (int iNode = 0; iNode < pNode->m_pChildList.size(); ++iNode)
        {
            //m_bUsedIndexList

            BuildTree(pNode->m_pChildList[iNode]);
        }

    }
   




}
void CQuadTree::FindDrawNode(CNode* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    bool collision = false;
    if (CoreInterface::g_pMainCamera->ClassifyOBB(&pNode->m_Box))
    {
        DrawNodeList.push_back(pNode);
        collision = true;

    }
    if (!collision)
    {
        for (int i = 0; i < pNode->m_pChildList.size(); ++i)
        {
            FindDrawNode(pNode->m_pChildList[i]);
        }
    }

   
}
void CQuadTree::PreOrder(CNode* pNode, CPlane* plane)
{


    if (pNode == nullptr)
    {
        return;
    }
   
    for (int i = 0; i < pNode->m_pChildList.size(); ++i)
    {
        PreOrder(pNode->m_pChildList[i], plane);
    }
    if (pNode->m_bIsLeaf)
    {
        //for (int iPlain = 0; iPlain < 6; iPlain++)
        //{
        //  
        //  //if (!CCollision::BoxToPlane(pNode->m_Box, plane[iPlain]))
        //  //{
        //  //    return;
        //  //}
        // if (!CCollision::SphereToPlane(pNode->m_Sphere, plane[iPlain]))
        // {
        //   
        //     return;
        // }
        //    
        //}
        //DrawNodeList.push_back(pNode);
        if (CoreInterface::g_pMainCamera->ClassifyOBB(&pNode->m_Box))
        {
            DrawNodeList.push_back(pNode);
        }


    }
   

}
void CQuadTree::PostOrder(CNode* pNode)
{



    if (pNode == nullptr)
    {
        return;
    }

    for (int i = 0; i < pNode->m_pChildList.size(); ++i)
    {
        PostOrder(pNode->m_pChildList[i]);
    }

 

}
void CQuadTree::LevelOrder(CNode* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }


    for (int i = 0; i < pNode->m_pChildList.size(); ++i)
    {
        m_pQueue.push(pNode->m_pChildList[i]);
    }

    if (!m_pQueue.empty())
    {
        CNode* Node = m_pQueue.front();
        m_pQueue.pop();
        LevelOrder(Node);
    }





}
CNode* CQuadTree::GetRootNode()
{
    return m_pRootNode;
}
TVector2	CQuadTree::GetHeightFromNode(DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR)
{

    DWORD dwStartRow = dwTL / m_pMap->m_iCol;
    DWORD dwEndRow = dwBL / m_pMap->m_iCol;

    DWORD dwStartCol = dwTL % m_pMap->m_iCol;
    DWORD dwEndCol = dwTR % m_pMap->m_iCol;

    TVector2 vHeight;
    vHeight.x = -999999.0f;
    vHeight.y = 999999.0f;

    // 0,  4, 
    // 20 ,24

    for (DWORD dwRow = dwStartRow; dwRow < dwEndRow; dwRow++)
    {
        for (DWORD dwCol = dwStartCol; dwCol < dwEndCol; dwCol++)
        {
            if (m_pMap->m_vVertexList[dwRow * m_pMap->m_iCol + dwCol].Pos.y > vHeight.x)
            {
                vHeight.x = m_pMap->m_vVertexList[dwRow * m_pMap->m_iCol + dwCol].Pos.y;
            }
            if (m_pMap->m_vVertexList[dwRow * m_pMap->m_iCol + dwCol].Pos.y < vHeight.y)
            {
                vHeight.y = m_pMap->m_vVertexList[dwRow * m_pMap->m_iCol + dwCol].Pos.y;
            }
        }
    }
    return vHeight;
}

TVector2 CQuadTree::GetHeightFromNode(CNode* pNode)
{
    DWORD dwTL = pNode->m_CornerIndex[0];
    DWORD dwTR = pNode->m_CornerIndex[1];
    DWORD dwBR = pNode->m_CornerIndex[2];
    DWORD dwBL = pNode->m_CornerIndex[3];

    DWORD dwStartCol = dwTL % m_pMap->m_iCol;
    DWORD dwEndCol = dwTR % m_pMap->m_iCol;
    DWORD dwStartRow = dwTL / m_pMap->m_iCol;
    DWORD dwEndRow = dwBL / m_pMap->m_iCol;

    TVector2 vHeight;
    vHeight.x = -99999999.0f;
    vHeight.y = 99999999.0f;

    for (int dwRow = dwStartRow; dwRow < dwEndRow; dwRow++)
    {
        for (int dwCol = dwStartCol; dwCol < dwEndCol; dwCol++)
        {
            DWORD dwCurrent = dwRow * m_pMap->m_iCol + dwCol;
            if (m_pMap->m_vVertexList[dwCurrent].Pos.y > vHeight.x)
            {
                vHeight.x = m_pMap->m_vVertexList[dwCurrent].Pos.y;
            }
            if (m_pMap->m_vVertexList[dwCurrent].Pos.y < vHeight.y)
            {
                vHeight.y = m_pMap->m_vVertexList[dwCurrent].Pos.y;
            }
        }
    }
    return vHeight;

}

void CQuadTree::CreateBoundingBox(CNode* pNode)
{
    DWORD dwV0 = pNode->m_CornerIndex[0];
    DWORD dwV1 = pNode->m_CornerIndex[3];

    //TVector2 vHeight = GetHeightFromNode(pNode->m_CornerIndex[0], pNode->m_CornerIndex[1],
    //    pNode->m_CornerIndex[2], pNode->m_CornerIndex[3]);
    TVector2 vHeight = GetHeightFromNode(pNode);
    pNode->m_Box.m_Max.x = m_pMap->m_vVertexList[dwV1].Pos.x;
    pNode->m_Box.m_Max.z = m_pMap->m_vVertexList[dwV0].Pos.z;
    pNode->m_Box.m_Min.x = m_pMap->m_vVertexList[dwV0].Pos.x;
    pNode->m_Box.m_Min.z = m_pMap->m_vVertexList[dwV1].Pos.z;


    pNode->m_Box.m_Max.y = vHeight.x;
    pNode->m_Box.m_Min.y = vHeight.y;

    pNode->m_Box.m_vAxis[0] = { 1,0,0 };
    pNode->m_Box.m_vAxis[1] = { 0,1,0 };
    pNode->m_Box.m_vAxis[2] = { 0,0,1 };

    pNode->m_Box.m_pCenter = (pNode->m_Box.m_Max + pNode->m_Box.m_Min) * 0.5f;
    pNode->m_Box.m_fExtent[0] = pNode->m_Box.m_Max.x - pNode->m_Box.m_pCenter.x;
    pNode->m_Box.m_fExtent[1] = pNode->m_Box.m_Max.y - pNode->m_Box.m_pCenter.y;
    pNode->m_Box.m_fExtent[2] = pNode->m_Box.m_Max.z - pNode->m_Box.m_pCenter.z;

    pNode->m_Box.m_Width = pNode->m_Box.m_Max.x - pNode->m_Box.m_Min.x;
    pNode->m_Box.m_height = pNode->m_Box.m_Max.y - pNode->m_Box.m_Min.y;
    pNode->m_Box.m_Depth = pNode->m_Box.m_Max.z - pNode->m_Box.m_Min.z;
    //todo
    pNode->m_Sphere.vCenter = pNode->m_Box.m_pCenter;
    pNode->m_Sphere.fRadius = fabs(pNode->m_Box.m_height);

    
    // create box 

  
}


CNode* CQuadTree::CreateNode(CNode* pParent,DWORD LT ,DWORD RT , DWORD LB,DWORD RB)
{
    CNode* NewNode = new CNode(pParent, LT, RT, LB, RB);

    NewNode->m_pChildList.reserve(4);
    NewNode->m_pCornerList.reserve(4);

    
    int iFace = (RT - LT) * (RT - LT) * 2;
    NewNode->m_vIndexList.resize(iFace * 3);

    int CurIndex = 0;

    for (int iRow = 0; iRow < RT-LT; iRow++)
    {
        for (int iCol = LT; iCol < RT; ++iCol)
        {
            int NextRow = iRow + 1;
            int NextCol = iCol + 1;

           NewNode->m_vIndexList[CurIndex + 0] = iRow * m_pMap->m_iCol + iCol;
           NewNode->m_vIndexList[CurIndex + 1] = iRow * m_pMap->m_iCol + NextCol;
           NewNode->m_vIndexList[CurIndex + 2] = NextRow * m_pMap->m_iCol + iCol;
           
           NewNode->m_vIndexList[CurIndex + 3] = NewNode->m_vIndexList[CurIndex + 2];
           NewNode->m_vIndexList[CurIndex + 4] = NewNode->m_vIndexList[CurIndex + 1];
           NewNode->m_vIndexList[CurIndex + 5] = NextRow * m_pMap->m_iCol + NextCol;
          
            CurIndex += 6;
        }
       
    }

    NewNode->CreateIndexBuffer();
    CreateBoundingBox(NewNode);
    UpdateVertexList(NewNode);
    NewNode->CreateVertexBuffer();
    //m_pLeafNodeList.push_back(NewNode);

    if (pParent)
    {
        NewNode->m_iDepth = pParent->m_iDepth + 1;
        if ((DWORD)m_iMaxDepth < NewNode->m_iDepth)
        {
            m_iMaxDepth = NewNode->m_iDepth;
        }
    }
 
   return NewNode;

}

bool CQuadTree::UpdateVertexList(CNode* pNode)
{

    int iNumCols = m_pMap->m_iCol;
    int iStartRow = pNode->m_CornerIndex[0] / iNumCols;
    int iEndRow = pNode->m_CornerIndex[2] / iNumCols;
    int iStartCol = pNode->m_CornerIndex[0] % iNumCols;
    int iEndCol = pNode->m_CornerIndex[1] % iNumCols;

    int iNumColCell = iEndCol - iStartCol;
    int iNumRowCell = iEndRow - iStartRow;
    pNode->m_vVertexList.resize((iEndCol - iStartCol + 1) * (iEndRow - iStartRow + 1));

    int iIndex = 0;
    for (int iRow = iStartRow; iRow <= iEndRow; iRow++)
    {
        for (int iCol = iStartCol; iCol <= iEndCol; iCol++)
        {
            int iCurrentIndex = iRow * iNumCols + iCol;
            pNode->m_vVertexList[iIndex++] = m_pMap->m_vVertexList[iCurrentIndex];
        }
    }
    if (pNode->m_vVertexList.size() > 0) return true;
    return false;

}


void CQuadTree::DebugBox(CBox box, CSphere sphere)
{
    shared_ptr<CObject> TestBox = make_shared<CObject>();
    TestBox->m_vVertexList.resize(24);
    float w2 = box.m_Max.x;
    float h2 = box.m_Max.y;
    float d2 = box.m_Max.z;

    float w3 = box.m_Min.x;
    float h3 = box.m_Min.y;
    float d3 = box.m_Min.z;

    // �ո�
    TestBox->m_vVertexList[0] = PNCT_VERTEX{ TVector3(w3, h3, d3), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[1] = PNCT_VERTEX{ TVector3(w3, +h2, d3), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[2] = PNCT_VERTEX{ TVector3(+w2, +h2, d3), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[3] = PNCT_VERTEX{ TVector3(+w2, h3, d3), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    // �޸� ->                                                         TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[4] = PNCT_VERTEX{ TVector3(w3, h3, +d2), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[5] = PNCT_VERTEX{ TVector3(+w2, h3, +d2), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[6] = PNCT_VERTEX{ TVector3(+w2, +h2, +d2), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[7] = PNCT_VERTEX{ TVector3(w3, +h2, +d2), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    // ���� ->
    TestBox->m_vVertexList[8] = PNCT_VERTEX{ TVector3(w3, +h2, d3),TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[9] = PNCT_VERTEX{ TVector3(w3, +h2, +d2),TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[10] = PNCT_VERTEX{ TVector3(+w2, +h2, +d2), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[11] = PNCT_VERTEX{ TVector3(+w2, +h2, d3), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    // �Ʒ�- >
    TestBox->m_vVertexList[12] = PNCT_VERTEX{ TVector3(w3, h3, d3), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[13] = PNCT_VERTEX{ TVector3(+w2, h3, d3), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[14] = PNCT_VERTEX{ TVector3(+w2, h3, +d2), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[15] = PNCT_VERTEX{ TVector3(w3, h3, +d2), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    // ����- >
    TestBox->m_vVertexList[16] =PNCT_VERTEX{ TVector3(w3, h3, +d2), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[17] =PNCT_VERTEX{ TVector3(w3, +h2, +d2), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[18] =PNCT_VERTEX{ TVector3(w3, +h2, d3), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[19] =PNCT_VERTEX{ TVector3(w3, h3, d3), TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    // ����->��																
    TestBox->m_vVertexList[20] = PNCT_VERTEX{ TVector3(+w2, h3, d3),TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[21] = PNCT_VERTEX{ TVector3(+w2, +h2, d3),TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[22] = PNCT_VERTEX{ TVector3(+w2, +h2, +d2),TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->m_vVertexList[23] = PNCT_VERTEX{ TVector3(+w2, h3, +d2),TVector3(0.0f, 1.0f,0.0f) ,TVector4(0.0f,0.0f,1.0f,1.0f),TVector2(0.0f,0.0f) };
    TestBox->CreateVertexBuffer();
    TestBox->m_vIndexList.resize(36);
    
    // �ո�
    TestBox->m_vIndexList[0] = 0; TestBox->m_vIndexList[1] = 1; TestBox->m_vIndexList[2] = 2;
    TestBox->m_vIndexList[3] = 0; TestBox->m_vIndexList[4] = 2; TestBox->m_vIndexList[5] = 3;
    // �޸�
    TestBox->m_vIndexList[6] = 4; TestBox->m_vIndexList[7] = 5; TestBox->m_vIndexList[8] = 6;
    TestBox->m_vIndexList[9] = 4; TestBox->m_vIndexList[10] = 6; TestBox->m_vIndexList[11] = 7;
    // ����
    TestBox->m_vIndexList[12] = 8; TestBox->m_vIndexList[13] = 9; TestBox->m_vIndexList[14] = 10;
    TestBox->m_vIndexList[15] = 8; TestBox->m_vIndexList[16] = 10; TestBox->m_vIndexList[17] = 11;
    // �Ʒ���
    TestBox->m_vIndexList[18] = 12; TestBox->m_vIndexList[19] = 13; TestBox->m_vIndexList[20] = 14;
    TestBox->m_vIndexList[21] = 12; TestBox->m_vIndexList[22] = 14; TestBox->m_vIndexList[23] = 15;
    // ���ʸ�
    TestBox->m_vIndexList[24] = 16; TestBox->m_vIndexList[25] = 17; TestBox->m_vIndexList[26] = 18;
    TestBox->m_vIndexList[27] = 16; TestBox->m_vIndexList[28] = 18; TestBox->m_vIndexList[29] = 19;
    // �����ʸ�
    TestBox->m_vIndexList[30] = 20; TestBox->m_vIndexList[31] = 21; TestBox->m_vIndexList[32] = 22;
    TestBox->m_vIndexList[33] = 20; TestBox->m_vIndexList[34] = 22; TestBox->m_vIndexList[35] = 23;

    /*
    PNCT_VERTEX v;
    float radius = sphere.fRadius; // ���� ������
    int stackCount = 10; // ���� ����
    int sliceCount = 10; // ���� ����
    // �ϱ�
    v.Pos = TVector3(sphere.vCenter.x, sphere.vCenter.y, sphere.vCenter.z);
    v.Tex = TVector2(0.5f, 0.0f);
    TestBox->m_vVertexList.push_back(v);

    float stackAngle = XM_PI / stackCount;
    float sliceAngle = XM_2PI / sliceCount;

    float deltaU = 1.f / static_cast<float>(sliceCount);
    float deltaV = 1.f / static_cast<float>(stackCount);

    // ������ ���鼭 ������ ����Ѵ� (�ϱ�/���� �������� ���� X)
    for (int y = 1; y <= stackCount - 1; ++y)
    {
        float phi = y * stackAngle;

        // ���� ��ġ�� ����
        for (int x = 0; x <= sliceCount; ++x)
        {
            float theta = x * sliceAngle;

            v.Pos.x = sphere.vCenter.x+radius * sinf(phi) * cosf(theta);
            v.Pos.y = sphere.vCenter.y+radius * cosf(phi);
            v.Pos.z = sphere.vCenter.z+radius * sinf(phi) * sinf(theta);

            v.Tex = TVector2(deltaU * x, deltaV * y);
            v.Nor = v.Pos;
            v.Nor.Normalize();


            TestBox->m_vVertexList.push_back(v);
        }
    }

    // ����
    v.Pos = TVector3(sphere.vCenter.x, -sphere.vCenter.y, sphere.vCenter.z);
    v.Nor = v.Nor;
    v.Nor.Normalize();
    TestBox->m_vVertexList.push_back(v);



    // �ϱ� �ε���
    for (int i = 0; i <= sliceCount; ++i)
    {
        //  [0]
        //   |  \
   		//  [i+1]-[i+2]
        TestBox->m_vIndexList.push_back(0);
        TestBox->m_vIndexList.push_back(i + 2);
        TestBox->m_vIndexList.push_back(i + 1);
    }

    // ���� �ε���
    int ringVertexCount = sliceCount + 1;
    for (int y = 0; y < stackCount - 2; ++y)
    {
        for (int x = 0; x < sliceCount; ++x)
        {
            //  [y, x]-[y, x+1]
            //  |		/
            //  [y+1, x]
            TestBox->m_vIndexList.push_back(1 + (y)*ringVertexCount + (x));
            TestBox->m_vIndexList.push_back(1 + (y)*ringVertexCount + (x + 1));
            TestBox->m_vIndexList.push_back(1 + (y + 1) * ringVertexCount + (x));
            //		 [y, x+1]
            //		 /	  |
            //  [y+1, x]-[y+1, x+1]
            TestBox->m_vIndexList.push_back(1 + (y + 1) * ringVertexCount + (x));
            TestBox->m_vIndexList.push_back(1 + (y)*ringVertexCount + (x + 1));
            TestBox->m_vIndexList.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
        }
    }

    // ���� �ε���
    int bottomIndex = static_cast<int>(TestBox->m_vVertexList.size()) - 1;
    int lastRingStartIndex = bottomIndex - ringVertexCount;
    for (int i = 0; i < sliceCount; ++i)
    {
        //  [last+i]-[last+i+1]
        //  |      /
        //  [bottom]
        TestBox->m_vIndexList.push_back(bottomIndex);
        TestBox->m_vIndexList.push_back(lastRingStartIndex + i);
        TestBox->m_vIndexList.push_back(lastRingStartIndex + i + 1);
    }
    */

    TestBox->Create(L"", L"../../Resource/Plane.hlsl");
    
    TestBoxlist.push_back(TestBox);
}

bool CQuadTree::Init()
{
    return true;
}

bool CQuadTree::PreFrame()
{
    return true;
}

bool CQuadTree::Frame()
{




    return true;
}

bool CQuadTree::PostFrame()
{
    return true;
}

bool CQuadTree::Render(CPlane* plane)
{
    m_pMap->SetMatrix(nullptr, &CoreInterface::g_pMainCamera->m_ViewMatrix, &CoreInterface::g_pMainCamera->m_ProjMatrix);
    m_pMap->PreRender();
    for (auto node : DrawNodeList)
    {
        node->Render();
    }

 //for (auto geo : TestBoxlist)
 //{
 //    geo->SetMatrix(nullptr, &CoreInterface::g_pMainCamera->m_ViewMatrix, &CoreInterface::g_pMainCamera->m_ProjMatrix);
 //     
 //    geo->Render();
 //}


    return true;
}

bool CQuadTree::Release()
{
    if (m_pRootNode)m_pRootNode->Release();
    if (m_pMap)m_pMap->Release();
    return true;
}



void CQuadTree::BuildQuadTree(CMap* pMap, DWORD Width, DWORD Height, std::vector<PNCT_VERTEX> vVertexList)
{
    
    m_bUsedIndexList = true;
    m_Width= Width;
    m_Height= Height;
    m_pMap = pMap;
    m_vVertexList.reserve(vVertexList.size());
    m_vVertexList = vVertexList;
    m_pRootNode = CreateNode(nullptr, 0, Width - 1, Width * (Height - 1), Width * Height - 1);
    m_pRootNode->m_iCellRow = Height;
    m_pRootNode->m_iCellCol= Width;
    BuildTree(m_pRootNode);


}

bool CQuadTree::SubDivide(CNode* pNode)
{
    if (pNode == NULL) return false;



    // ���� ����� ���� ũ�⸦ ����Ѵ�.
    DWORD dwOffsetX = (pNode->m_CornerIndex[1] - pNode->m_CornerIndex[0]);
    DWORD dwOffsetZ = ((pNode->m_CornerIndex[2] - pNode->m_CornerIndex[0]) / m_Width);

    DWORD dwWidthSplit = CheckSize(dwOffsetX);
    DWORD dwHeightplit = CheckSize(dwOffsetZ);

    // �ִ� ���� �ѵ��� �����Ѵ�.
    if ((DWORD)m_iMaxDepthLimit <= pNode->m_iDepth)
    {
        pNode->m_bIsLeaf = TRUE;
       
            DebugBox(pNode->m_Box, pNode->m_Sphere);
        //CreateVertexList(pNode);
        return false;
    }
    // 4��� �Ҽ� ������ ���̻� �������� �ʴ´�.
    if (dwWidthSplit < (DWORD)m_iMinSplitDistance || dwHeightplit < (DWORD)m_iMinSplitDistance)
    {
        pNode->m_bIsLeaf = TRUE;
      
            DebugBox(pNode->m_Box, pNode->m_Sphere);
        //CreateVertexList(pNode);
        return false;
    }
    // �ڽ� ��尡 ������ ����ũ�⺸�� �۴ٸ� ���̻� �������� �ʴ´�.
    if (dwWidthSplit < m_fMinDivideSize || dwHeightplit < m_fMinDivideSize)
    {
        pNode->m_bIsLeaf = TRUE;
      
            DebugBox(pNode->m_Box, pNode->m_Sphere);
       //CreateVertexList(pNode);
        return false;
    }

    // ���� = �����ڳ� + ���ø�ũ��
    // ���ϱ� = ���� + ( ���ø� ũ�� * ��ü�� ����ũ�� )
    DWORD dwSplitCenter = (pNode->m_CornerIndex[0] + dwWidthSplit) + (dwHeightplit * m_Width);

    DWORD dwEdgeCenter[4];
    dwEdgeCenter[0] = pNode->m_CornerIndex[0] + dwWidthSplit;
    dwEdgeCenter[1] = pNode->m_CornerIndex[1] + dwHeightplit * m_Width;
    dwEdgeCenter[2] = pNode->m_CornerIndex[2] + dwWidthSplit;
    dwEdgeCenter[3] = pNode->m_CornerIndex[0] + dwHeightplit * m_Width;

    pNode->m_pChildList.push_back(CreateNode(pNode, pNode->m_CornerIndex[0],
        dwEdgeCenter[0],
        dwEdgeCenter[3],
        dwSplitCenter));

    pNode->m_pChildList.push_back(CreateNode(pNode, dwEdgeCenter[0],
        pNode->m_CornerIndex[1],
        dwSplitCenter,
        dwEdgeCenter[1]));

    pNode->m_pChildList.push_back(CreateNode(pNode, dwEdgeCenter[3],
        dwSplitCenter,
        pNode->m_CornerIndex[2],
        dwEdgeCenter[2]));

    pNode->m_pChildList.push_back(CreateNode(pNode, dwSplitCenter,
        dwEdgeCenter[1],
        dwEdgeCenter[2],
        pNode->m_CornerIndex[3]));
    return true;
}
DWORD CQuadTree::CheckSize(DWORD dwSize)
{
    float fCount = 0;
    DWORD dwChecker = dwSize / 2;
    if (dwChecker <= 0) return 0;

    while (dwChecker != 0)
    {
        dwChecker >>= 1;
        fCount += 1.0f;
    }
    float fMinimum = pow(2.0f, fCount - 1.0f);
    float fMaximum = pow(2.0f, fCount);
    // fMin = abs( fMin - P0 ) - abs( P1 - fMin );
    // fMax = abs( fMax - P0 ) - abs( P1 - fMax );
    // return min( fMin, fMax );
    float fMin = fabs(fMinimum - fabs(((float)dwSize - fMinimum)));
    float fMax = fabs(fMaximum - fabs(((float)dwSize - fMaximum)));

    // �񱳰��� ���ٸ� ���� ����ũ�⸦ ��ȯ�Ѵ�. ��) fMin=1 : fMax=1 => fMinimum=2 : fMaximum=4
    if (fMin <= fMax)
    {
        return (DWORD)fMinimum;
    }
    return (DWORD)fMaximum;
}

