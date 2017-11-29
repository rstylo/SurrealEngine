#ifndef RENDERER_H_
#define RENDERER_H_

#include <d3d9.h> // direct3d 

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	virtual bool Init(HWND, bool);				//params: handel device + in windowed of niet?
	virtual void Clear(D3DCOLOR);			 //gebruikt om back buffer frames te clearen
	virtual void Begin();
	virtual void End();
	virtual void Present();

	LPDIRECT3DDEVICE9 device;					//(staat voor long pointer naar d3d device), 
												//weet de voordelen er niet van over "normale" pointer(IDirect3DDevice9* device), alleen dat het een gedoe om het te deleten
												//daarom is het fijn dat om deze manier met ->Release of ->reset pointer vrij gemaakt kan worden..
private:

	LPDIRECT3D9 direct3d;						//direct3d zlf, dus hier kan ook LPDIRECT3D9* direct3d;

};

#endif // RENDERER_H_