#include "CMapObj.h"

bool CMapObj::Frame()
{
    TMatrix matrixSCale;
    TMatrix matrixRotate;
    TMatrix matrixtrans;
    D3DXMatrixScaling(&matrixSCale, m_vScale.x, m_vScale.y, m_vScale.z);
    D3DXMatrixRotationZ(&matrixRotate, m_vRotate.z);
    D3DXMatrixTranslation(&matrixSCale, m_vPos.x, m_vPos.y, m_vPos.z);

    m_WolrdMatrix = matrixSCale * matrixRotate * matrixtrans;

    return true;
}
