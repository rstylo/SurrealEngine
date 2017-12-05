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




#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
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

bool Renderer::Init(HWND hWnd, bool windowed)
{
	//drd pointer met variablen
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);  //D3D9b_SDK_VERSION??

	//belangrijkje params voor d3d deviice
	D3DPRESENT_PARAMETERS presParams;				//"presentation" parameters
	ZeroMemory(&presParams, sizeof(presParams));
	
	presParams.hDeviceWindow = hWnd;
	presParams.Windowed = windowed;
	presParams.SwapEffect = D3DSWAPEFFECT_DISCARD;	//snelste mogelijkheid, geen overhead die wel hebt bij andere swapeffecten zie msdn
	

	//copy van tut06
	/*
	presParams.Windowed = TRUE;
	presParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presParams.BackBufferFormat = D3DFMT_UNKNOWN;
	presParams.EnableAutoDepthStencil = TRUE;
	presParams.AutoDepthStencilFormat = D3DFMT_D16;
	*/

	if (!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &presParams, &device))) //mixed vortex = gecompineerd hardware n software 3d berekeningen
	{
		MessageBox(NULL, "issue creating gfx device", NULL, NULL);
		return false;
	}

	// Turn on the zbuffer
	device->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Turn on ambient lighting 
	device->SetRenderState(D3DRS_AMBIENT, 0xffffffff);


	return true;


}

void Renderer::Clear(D3DCOLOR color)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);	//backbuffer clear 

}

void Renderer::Begin() {
	device->BeginScene();
}

void Renderer::End() {
	device->EndScene();
}

void Renderer::Present() {
	device->Present(NULL, NULL, NULL, NULL);	//waarom 4 nullen niet 6 zoals bij leraar?
}