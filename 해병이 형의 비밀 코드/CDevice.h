#pragma once
#include "CWindow.h"
class CDevice :public CWindow
{
public:
	ComPtr<IDXGISwapChain>			 m_pSwapChain = nullptr;
	DXGI_SWAP_CHAIN_DESC			 m_SwapChainDesc;
	ComPtr<ID3D11Device>			 m_pDevice = nullptr;
	ComPtr<ID3D11DeviceContext>		 m_pImmediateContext = nullptr;
	ComPtr<ID3D11RenderTargetView>   m_pRenderTargetView;
	D3D_FEATURE_LEVEL				 m_pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_DRIVER_TYPE					 m_DriverType = D3D_DRIVER_TYPE_HARDWARE;
	ComPtr <IDXGIFactory>			 m_pFactory=nullptr;
	ComPtr<ID3D11DepthStencilView>	 m_pDepthStencilView = nullptr;
	D3D11_VIEWPORT					 m_ViewPort;

public:
	bool CreateDevice();
	bool CreateDepthStencilView();
	bool CreateFactory();
	bool CreateSwapChain();
	bool SetRenderTarGetView();
	bool SetViewPort();

public:
	bool Init();
	bool Frame();
	
	bool PreRender();
	bool PostRender();
	bool Render();
	bool Release();

};

