#include "CoreInterface.h"


ID3D11Device*		 CoreInterface:: g_pDevice = nullptr;
ID3D11DeviceContext* CoreInterface::g_pImmediateContext = nullptr;
CCamera* CoreInterface::g_pMainCamera = nullptr;