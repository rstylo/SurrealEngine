/*

Hier wat info over delete en release
you call reset and it frees the old one.To free it without replacement, you call release.When it goes out of scope, it's destroyed

1) delete
delete de-allocates the memory allocated by new operator.
Its part of standard C++.
2) Release
Release is related with COM interface.
It decrease the reference count of the specified interface.


*/




#include "DirectXRenderer.h"



DirectXRenderer::DirectXRenderer()
{
}


DirectXRenderer::~DirectXRenderer()
{
	if (device != NULL)
	{
		device->Release();					//release gebruiken omdat er geen new werd gebruikt om de object te creëren, en er is gebruik van auto/smart pointer (weet niet precies de werking van long pointer)
		device = NULL;
	}

	if (direct3d != NULL)
	{
		direct3d->Release();
		direct3d = NULL;
	}
}

bool DirectXRenderer::Init(HWND hWnd, bool windowed)
{
	//drd pointer met variablen
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);  //D3D9b_SDK_VERSION??



	//belangrijkje params voor d3d deviice
	D3DPRESENT_PARAMETERS presParams;				//"presentation" parameters
	ZeroMemory(&presParams, sizeof(presParams));

	presParams.hDeviceWindow = hWnd;
	presParams.Windowed = windowed;
	presParams.BackBufferCount = 1;
	presParams.BackBufferFormat = D3DFMT_UNKNOWN;
	presParams.MultiSampleType = D3DMULTISAMPLE_NONE;		// "anti ailising"
	presParams.MultiSampleQuality = 0;
	//presParams.Flags = 0;
	//presParams.EnableAutoDepthStencil = true;
	//presParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	//presParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//presParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	presParams.SwapEffect = D3DSWAPEFFECT_DISCARD;	//snelste mogelijkheid, geen overhead die wel hebt bij andere swapeffecten zie msdn

	if (!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presParams, &device))) //mixed vortex = gecompineerd hardware n software 3d berekeningen
	{
		MessageBox(NULL, "issue creating gfx device", NULL, NULL);
		return false;
	}

	// Turn off culling, so we see the front and back of the triangle
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	// Turn off D3D lighting, since we are providing our own vertex colors
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return true;


}

void DirectXRenderer::Clear(D3DCOLOR color)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);	//backbuffer clear 

}

bool DirectXRenderer::Begin() {
	if(SUCCEEDED(device->BeginScene()))
	{
		return true;
	}
	return false;
}

void DirectXRenderer::End() {
	device->EndScene();
}

void DirectXRenderer::Present(HWND wnd) {
	device->Present(NULL, NULL, wnd, NULL);
}

LPDIRECT3DDEVICE9* DirectXRenderer::GetDevice()
{
	return &device;
}

