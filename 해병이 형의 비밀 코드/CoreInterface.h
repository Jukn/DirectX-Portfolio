#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include"CCamera.h"
class CoreInterface
{
public:
	static ID3D11Device* g_pDevice ;
	static ID3D11DeviceContext* g_pImmediateContext;
	static CCamera* g_pMainCamera;
	
};

