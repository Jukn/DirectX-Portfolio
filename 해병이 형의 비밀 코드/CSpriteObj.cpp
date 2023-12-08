#include "CSpriteObj.h"
#include"CoreInterface.h"
bool CSpriteObj::Load(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, CSpriteData data)
{
    Set(pDevice, pImmediateContext);
    SetPos(data.m_vPos);
    SetScale(data.m_vScale);

    LoadTexData(data.m_TextureList);
    SetUVData(data.iRow, data.iCol);
    Create(data.FileName, data.ShaderName);
    this->SpriteInfo.m_fDelay = data.m_fDelay;

    return true;
}

bool CSpriteObj::LoadTexData(std::vector<std::wstring> TexList)
{

    return true;
}
bool CSpriteObj::SetUVData(int iNumRow, int iNumColumn)
{
    
    return true;
}
bool CSpriteTexObj::LoadTexData(std::vector<std::wstring> TexList)
{
    for (auto& Tex : TexList)
    {
        const CTexture* Newtex = CTextureMgr::GetInstance().Load(Tex);
        m_pTextureList.push_back(Newtex);
    }

    return true;
}

bool CSpriteTexObj::Init()
{
    CPlaneObj::Init();
   
    return true;
}
bool CSpriteTexObj::Frame()
{
    CPlaneObj::Frame();



    m_AccumulatedTime += g_fSecondPerFrame;
    if (m_pTextureList[m_iTexIndex] != nullptr)
    {
        if (m_AccumulatedTime >= SpriteInfo.m_fDelay)
        {
           m_iTexIndex++;
            if (m_iTexIndex >= m_pTextureList.size())
            {

                m_iTexIndex = 0;
            }
            m_AccumulatedTime -= SpriteInfo.m_fDelay;
        }

    }


    return true;
}
bool CSpriteTexObj::Render()
{
    PreRender();
    m_pTextureList[m_iTexIndex]->Apply(CoreInterface::g_pImmediateContext, 0);
    PostRender();

    return true;
}
bool CSpriteTexObj::Release()
{
   
    CPlaneObj::Release();
    return true;
}
CSpriteTexObj::CSpriteTexObj()
{
    Init();
};
CSpriteTexObj:: ~CSpriteTexObj()
{
    Release();
};



bool CSpriteUVObj::SetUVData(int iNumRow, int iNumColumn)
{
    CUVRect rect;
    TVector2 uv = { 0,0 };

    float OffSet = 1.0f / iNumColumn;

    float fOffsetX = 1.0f / iNumColumn;
    float fOffsetY = 1.0f / iNumRow;
    for (int row = 0; row < iNumRow; row++)
    {
        uv.y = fOffsetY * row;
        for (int column = 0; column < iNumColumn; column++)
        {
            uv.x = fOffsetX * column;
            rect.m_Min = uv;
            rect.m_Max.x = uv.x + fOffsetX;
            rect.m_Max.y = uv.y + fOffsetY;
            m_pUVList.push_back(rect);
        }
    }
  

    return true;
}

bool CSpriteUVObj::Init()
{
    CPlaneObj::Init();
  

    return true;
}
bool CSpriteUVObj::Frame()
{
   /* CVector2 rt = { m_vPos.x,m_vPos.y };
    SetRect(rt, m_vScale.x * 2.0f, m_vScale.y * 2.0f);*/
    CPlaneObj::Frame();

    m_AccumulatedTime += g_fSecondPerFrame;
   
        if (m_AccumulatedTime >=SpriteInfo.m_fDelay)
        {
            m_iTexIndex++;
            if (m_iTexIndex >= m_pUVList.size())
            {

                m_iTexIndex = 0;
            }
            m_AccumulatedTime -= SpriteInfo.m_fDelay;
        }

 


    return true;
}
bool CSpriteUVObj::Render(bool Face)
{
    PreRender();
    CUVRect uv = m_pUVList[m_iTexIndex];
    if (Face)
    {
       m_vVertexList[0].Tex.x = uv.m_Max.x;
       m_vVertexList[0].Tex.y = uv.m_Min.y;
       m_vVertexList[1].Tex = uv.m_Min;
       m_vVertexList[2].Tex = uv.m_Max;
       m_vVertexList[3].Tex = m_vVertexList[2].Tex;
       m_vVertexList[4].Tex = m_vVertexList[1].Tex;
       m_vVertexList[5].Tex.x = uv.m_Min.x;
       m_vVertexList[5].Tex.y = uv.m_Max.y;

    }
    else
    {
      m_vVertexList[0].Tex = uv.m_Min;
      m_vVertexList[1].Tex.x = uv.m_Max.x;
      m_vVertexList[1].Tex.y = uv.m_Min.y;

      m_vVertexList[2].Tex.x = uv.m_Min.x;
      m_vVertexList[2].Tex.y = uv.m_Max.y;


      m_vVertexList[3].Tex = m_vVertexList[2].Tex;
      m_vVertexList[4].Tex = m_vVertexList[1].Tex;

      m_vVertexList[5].Tex = uv.m_Max;
    }
    CoreInterface::g_pImmediateContext->UpdateSubresource(m_pVertexBuffer.Get(), 0, nullptr,&m_vVertexList.at(0), 0, 0);

    //CUVRect uv = m_pUVList[m_iTexIndex];
    //m_vVertexList[0].Tex = uv.m_Min;
    //m_vVertexList[1].Tex.x = uv.m_Max.x;
    //m_vVertexList[1].Tex.y = uv.m_Min.y;
    //m_vVertexList[2].Tex.x = uv.m_Min.x;
    //m_vVertexList[2].Tex.y = uv.m_Max.y;
    //m_vVertexList[3].Tex = m_vVertexList[2].Tex;
    //m_vVertexList[4].Tex = m_vVertexList[1].Tex;
    //m_vVertexList[5].Tex = uv.m_Max;


  
   PostRender();

    return true;
}
bool CSpriteUVObj::Release()
{
    CPlaneObj::Release();
    return true;
}
CSpriteUVObj::CSpriteUVObj()
{
    Init();
};
CSpriteUVObj:: ~CSpriteUVObj()
{
    Release();
};