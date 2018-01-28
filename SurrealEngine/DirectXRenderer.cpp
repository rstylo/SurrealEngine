#include "DirectXRenderer.h"
#include "logger.h"


DirectXRenderer::DirectXRenderer()
{
	logger.Logtime();
}


DirectXRenderer::~DirectXRenderer()
{
	//! releases directx and its device to free space
	if (device != NULL)
	{
		device->Release();					
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
	//! Initialise directx and its rendering device with a window in windowed or not.


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

	presParams.SwapEffect = D3DSWAPEFFECT_COPY;
	presParams.EnableAutoDepthStencil = TRUE;
	presParams.AutoDepthStencilFormat = D3DFMT_D16;

	//presParams.Flags = 0;
	//presParams.EnableAutoDepthStencil = true;
	//presParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	//presParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//presParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	presParams.SwapEffect = D3DSWAPEFFECT_DISCARD;	//snelste mogelijkheid, geen overhead die wel hebt bij andere swapeffecten zie msdn

	if (!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presParams, &device))) //mixed vortex = gecompineerd hardware n software 3d berekeningen
	{
		MessageBox(NULL, "issue creating gfx device", NULL, NULL);
		logger.Log("issue creating gfx device", "Error");
		return false;
	}

	// Turn off culling, so we see the front and back of the triangle
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//drawn on D3DCULL_CCW

	device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	// Turn off D3D lighting, since we are providing our own vertex colors
	device->LightEnable(0, TRUE);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_AMBIENT, 0x008D6056);


	return true;


}

void DirectXRenderer::Clear(D3DCOLOR color)
{
	//! clear the back buffer and zbuffer with a color for the background
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);	//backbuffer clear 
}

bool DirectXRenderer::Begin() {
	//! start the drawing process for a frame, returns false when unsuccesful

	if (SUCCEEDED(device->BeginScene()))
	{
		return true;
	}
	return false;
}

void DirectXRenderer::End() {
	//! Ends the frame

	device->EndScene();
}

void DirectXRenderer::Present(HWND wnd) {
	//! presents the created frame to the screen
	device->Present(NULL, NULL, wnd, NULL);
}

LPDIRECT3DDEVICE9* DirectXRenderer::GetDevice()
{
	//! get rendering device
	return &device;
}

void DirectXRenderer::Log(std::string text, std::string type)
{
	logger.Log(text, type);
}

void DirectXRenderer::Flush()
{
	logger.Flush();
}

