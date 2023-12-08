#include "CPlayerObj.h"
#include "CInput.h"
#include"CoreInterface.h"


void CPlayerObj::Move(double fSecond)
{
    if (Jump == false && Drop == false) BeforePos = m_vPos;
   
    if (m_bVaild == false)
    {
        return;
   }
   if (CInput::GetInstance().m_dwKeyState['W'] >= KEY_PUSH)
   {
       m_vPos.y += MoveSpeed * fSecond;
   }
  if (CInput::GetInstance().m_dwKeyState['S'] >= KEY_PUSH)
   {
       m_vPos.y -= MoveSpeed * fSecond;
   }
    if (CInput::GetInstance().m_dwKeyState['A'] >= KEY_HOLD)
    {
     
        FaceLeft = true;
        FaceRight = false;
        /*  if (MaxSpeed >= MoveSpeed)
        {
            MoveSpeed += 2100.0f * fSecond;
        }*/
        m_vPos.x -= MoveSpeed * fSecond;
       // MoveSpeed += 500.0f * fSecond;
        m_vVertexList[0].Tex = { 0.0f,0.0f };
        m_vVertexList[1].Tex = { 1.0f,0.0f };
        m_vVertexList[2].Tex = { 0.0f,1.0f };
        m_vVertexList[3].Tex = m_vVertexList[2].Tex;
        m_vVertexList[4].Tex = m_vVertexList[1].Tex;
        m_vVertexList[5].Tex = { 1.0f,1.0f };

        CoreInterface::g_pImmediateContext->UpdateSubresource(m_pVertexBuffer.Get(), 0, nullptr, &m_vVertexList.at(0), 0, 0);
       
    }
    if (CInput::GetInstance().m_dwKeyState['D'] >= KEY_PUSH)
    {
        IsMove = true;
        FaceRight = true;
        FaceLeft = false;
        /* if (MaxSpeed >= MoveSpeed)
        {
            MoveSpeed += 2100.0f * fSecond;
        }*/
       // MoveSpeed += 500.0f * fSecond;
        m_vPos.x += MoveSpeed * fSecond;
        
        m_vVertexList[0].Tex = { 1.0f,0.0f };
        m_vVertexList[1].Tex = { 0.0f,0.0f };
        m_vVertexList[2].Tex = { 1.0f,1.0f };
        m_vVertexList[3].Tex = m_vVertexList[2].Tex;
        m_vVertexList[4].Tex = m_vVertexList[1].Tex;
        m_vVertexList[5].Tex = { 0.0f,1.0f };

 
        CoreInterface::g_pImmediateContext->UpdateSubresource(m_pVertexBuffer.Get(), 0, nullptr,&m_vVertexList.at(0), 0, 0);
        

    }
  //  if (CInput::GetInstance().m_dwKeyState[VK_SPACE] == KEY_PUSH&&Jump==false&&Drop==false)
  //  {
  //     //Roll = true;
  //      Jump = true;
  //  }
  //  if (CInput::GetInstance().m_dwKeyState[VK_SPACE] == KEY_HOLD)
  //  {
  //      if (Drop == false && Jump == false)
  //      {
  //         // Roll = true;
  //          Jump = true;
  //      }
  //  }
  // /* if (Roll == true) {
  //      m_vRotate.z += DegreeTORadian(fSecond * 1000.0f);
  //      if (m_vRotate.z >= PI * 4) {
  //          m_vRotate.z = 0.0f;
  //          Roll = false;
  //      }
  //  }*/
  //  if (Jump == true)
  //  {
  //      m_vPos.y += 600.0f * fSecond;
  //      if (m_vPos.y - BeforePos.y > fabs(150.0f)|| m_vPos.y >= (Map_YSize)-(m_vScale.y))
  //      {
  //          Jump = false;
  //          Drop = true;
  //      }
  //  }
  //  if (Drop == true)
  //  {
  //     
  //      if (MaxDropSpeed >= DropSpeed)
  //      {
  //          DropSpeed += 3500.0f * fSecond;
  //      }
  //      m_vPos.y -= DropSpeed * fSecond;
  //  }
  //  else
  //  {
  //      DropSpeed = 400.0f;
  //  }
  //  if (m_vPos.x <= -(Map_XSize) + (m_vScale.x))
  //  {
  //      m_vPos.x = -(Map_XSize ) + (m_vScale.x );
  //  }
  //  if (m_vPos.y <= -(Map_YSize ) + (m_vScale.y))
  //  
  //      m_vPos.y = -(Map_YSize ) + (m_vScale.y );
  //  }
  //  if (m_vPos.x >= (Map_XSize ) - (m_vScale.x ))
  //  {
  //      m_vPos.x = (Map_XSize ) - (m_vScale.x );
  //  }
  //  if (m_vPos.y >= (Map_YSize ) - (m_vScale.y))
  //  {
  //     m_vPos.y = (Map_YSize ) - (m_vScale.y );
  //  }
  ///*  CVector3 velocity = m_vDirection * fSecond * 500.0f;
  //  m_vPos = m_vPos + velocity;*/

  

}

void CPlayerObj::Turn()
{
   
}

bool CPlayerObj::Render()
{
    if (m_bVaild == false)
    {
        return true;
    }
    
        CUVRect uv = m_pUVList[m_iTexIndex];
        if (FaceLeft == true)
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
        else
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




        CoreInterface::g_pImmediateContext->UpdateSubresource(m_pVertexBuffer.Get(), 0, nullptr, &m_vVertexList.at(0), 0, 0);

        PreRender();
        PostRender();
    
       

 
    return true;
}
