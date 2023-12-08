#include "CPlaneObj.h"
#include "CInput.h"
#include"CoreInterface.h"
bool CPlaneObj::CreateVertexBuffer()
{
   

     m_vVertexList.resize(6);

     m_vVertexList[0].Pos = { -1.0f,1.0f,0.0f };
     m_vVertexList[1].Pos = { 1.0f,1.0f,0.0f };
     m_vVertexList[2].Pos = { -1.0f, -1.0f,0.0f };
     m_vVertexList[3].Pos = { -1.0f, -1.0f,0.0f };
     m_vVertexList[4].Pos = { 1.0f,1.0f,0.0f };
     m_vVertexList[5].Pos = { 1.0f ,-1.0f,0.0f };

     m_vVertexList[0].Tex = { 0.0f,0.0f };
     m_vVertexList[1].Tex = { 1.0f,0.0f };
     m_vVertexList[2].Tex = { 0.0f,1.0f };
     m_vVertexList[3].Tex = m_vVertexList[2].Tex;
     m_vVertexList[4].Tex = m_vVertexList[1].Tex;
     m_vVertexList[5].Tex = { 1.0f,1.0f };


     D3D11_BUFFER_DESC Desc;
     Desc.ByteWidth = sizeof(PNCT_VERTEX) * m_vVertexList.size();
     Desc.Usage = D3D11_USAGE_DEFAULT;
     Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
     Desc.CPUAccessFlags = 0;
     Desc.MiscFlags = 0;
     Desc.StructureByteStride = 0;
     D3D11_SUBRESOURCE_DATA InitialData;
     InitialData.pSysMem = &m_vVertexList.at(0);
     CoreInterface::g_pDevice->CreateBuffer(
         &Desc,
         &InitialData,
         m_pVertexBuffer.GetAddressOf());

    return true;
}

bool CPlaneObj::Frame()
{

    CObject::Frame();

    return true;
}
