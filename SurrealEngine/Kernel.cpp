#include "Kernel.h"

LPDIRECT3D9         d3d9device; // Used to create the D3DDevice
LPDIRECT3DDEVICE9   d3d9renderer; // Our rendering device
LPDIRECT3DDEVICE9   d3d9renderer2; // Our rendering device
WNDCLASSEX windowclass;
WNDCLASSEX windowclass2;
HWND window;
HWND window2;

Kernel::Kernel()
{

	windowclass = { sizeof(WNDCLASSEX), CS_CLASSDC, MessageHandler, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"Engine", NULL
	};

	windowclass2 = { sizeof(WNDCLASSEX), CS_CLASSDC, MessageHandler, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"Engine2", NULL
	};

	RegisterClassEx(&windowclass);
	RegisterClassEx(&windowclass2);

	window = CreateWindow(L"Engine", L"Surrealengine",
		WS_OVERLAPPEDWINDOW, 100, 100, 1268, 864,
		NULL, NULL, windowclass.hInstance, NULL);

	window2 = CreateWindow(L"Engine2", L"Surrealengine2",
		WS_OVERLAPPEDWINDOW, 500, 200, 1268, 864,
		NULL, NULL, windowclass2.hInstance, NULL);
	
	

	if (SUCCEEDED(InitD3D(window, window2)))
	{
		ShowWindow(window, SW_SHOWDEFAULT);
		UpdateWindow(window);

		ShowWindow(window2, SW_SHOWDEFAULT);
		UpdateWindow(window2);

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterClass(L"Engine", windowclass.hInstance);
	UnregisterClass(L"Engine2", windowclass2.hInstance);
}

Kernel::~Kernel()
{
}

HRESULT Kernel::InitD3D(HWND hWnd, HWND hWnd2)
{
	if (NULL == (d3d9device = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(d3d9device->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &d3d9renderer)))
	{
		return E_FAIL;
	}
/*	
	D3DPRESENT_PARAMETERS d3dpp2;
	ZeroMemory(&d3dpp2, sizeof(d3dpp2));
	d3dpp2.Windowed = TRUE;
	d3dpp2.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp2.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(d3d9device->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp2, &d3d9renderer2)))
	{
		return E_FAIL;
	}
*/
	// Device state would normally be set here

	return S_OK;
}

VOID Cleanup()
{
	if (d3d9renderer2 != NULL)
		d3d9renderer2->Release();

	if (d3d9renderer != NULL)
		d3d9renderer->Release();

	if (d3d9device != NULL)
		d3d9device->Release();
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	if (NULL == d3d9renderer)
		return;

	// Clear the backbuffer to a blue color
	d3d9renderer->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(d3d9renderer->BeginScene()))
	{
		// Rendering of scene objects can happen here

		// End the scene
		d3d9renderer->EndScene();
	}

	// Present the backbuffer contents to the display
	d3d9renderer->Present(NULL, NULL, NULL, NULL);
	/*
	if (NULL == d3d9renderer2)
		return;

	// Clear the backbuffer to a blue color
	d3d9renderer2->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(d3d9renderer2->BeginScene()))
	{
		// Rendering of scene objects can happen here

		// End the scene
		d3d9renderer2->EndScene();
	}

	// Present the backbuffer contents to the display
	d3d9renderer2->Present(NULL, NULL, NULL, NULL);
	*/
}

LRESULT WINAPI MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		Render();
		ValidateRect(hWnd, NULL);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
