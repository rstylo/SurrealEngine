#include "D3dHeightMap.h"



D3dHeightMap::D3dHeightMap()
{
	width = 0;
	depth = 0;

	heightData = NULL;
}


D3dHeightMap::~D3dHeightMap()
{
	CleanUp();
}

bool D3dHeightMap::LoadBMP()
{
	//! load height map from give path and inserts into heightmap data
	//! is called on program initialization
	HDC deviceContext;
	HANDLE bmp;
	HINSTANCE hInstance = NULL;


	deviceContext = CreateCompatibleDC(NULL);
	if (deviceContext == NULL)
	{
		DeleteDC(deviceContext);
		return false;
	}

	bmp = LoadImage(hInstance, heightMapFileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (bmp == NULL)
	{
		bmp = LoadImage(hInstance, ("..\\" + heightMapFileName).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (bmp == NULL) {
			char s[100];
			wsprintf(s, "Can't find HeightMask %s", heightMapFileName);
			MessageBox(NULL, s, "ERROR ERROR ERROR", MB_OK);
			return false;
		}
	}

	SelectObject(deviceContext, bmp);

	BITMAP bitmap;

	GetObject(bmp, sizeof(BITMAP), (void*)&bitmap);

	width = bitmap.bmWidth;
	depth = bitmap.bmHeight;

	heightData = new BYTE[width * depth];

	for (int itW = 0; itW < width; itW++)
	{
		for (int itH = 0; itH < depth; itH++)
		{
			heightData[itW * depth + itH] = GetRValue(GetPixel(deviceContext, itW, itH));
		}
	}
	return true;
}

std::string D3dHeightMap::GetMapFileName()
{
	return heightMapFileName;
}

void D3dHeightMap::SetMapFileName(std::string _heightMapFileName)
{
	heightMapFileName = _heightMapFileName;
}

void D3dHeightMap::CleanUp()
{
	if (heightData != NULL)
	{
		delete heightData;
		heightData = NULL;
	}
}

byte * D3dHeightMap::GetHeightData()
{
	return heightData;
}

int D3dHeightMap::GetWidth()
{
	return width;
}

int D3dHeightMap::GetDepth()
{
	return depth;
}
