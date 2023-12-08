#include "CNpcObj.h"
void CNpcObj::Move(double fSecond)
{


    TVector3 velocity = m_vDirection * fSecond * 500.0f;
    m_vPos = m_vPos + velocity;


    if (m_vPos.x <= -Map_XSize)
    {

        m_vDirection.x *= -1.0f;
        m_vPos.x = -Map_XSize;

    }
    if (m_vPos.y <= -Map_YSize)
    {

        m_vDirection.y *= -1.0f;
        m_vPos.y = -Map_YSize;

    }
    if (m_vPos.x >= Map_XSize)
    {

        m_vDirection.x *= -1.0f;
        m_vPos.x = Map_XSize;

    }
    if (m_vPos.y >= Map_YSize)
    {

        m_vDirection.y *= -1.0f;
        m_vPos.y = Map_YSize;

    }

   


}

bool CNpcObj::PreRender()
{
    CDxObject::PreRender();
    return true;
}

bool CNpcObj::Render()
{
    CDxObject::Render();
    return true;
}

bool CNpcObj::PostRender()
{
    CDxObject::PostRender();
    return true;
}

bool CNpcObj::Release()
{
    CPlaneObj::Release();
    return false;
}
