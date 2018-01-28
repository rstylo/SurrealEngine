#ifndef D3DHEIGHTMAP_H_
#define D3DHEIGHTMAP_H_

#include <string>
#include <cmath>
#include <d3dx9.h>

class D3dHeightMap
{
public:
	D3dHeightMap();
	virtual ~D3dHeightMap();

	virtual bool LoadBMP();
	
	virtual void CleanUp();

	virtual std::string GetMapFileName();
	virtual void SetMapFileName(std::string);
	virtual byte* GetHeightData();
	virtual int GetWidth();
	virtual int GetDepth();


private:
	std::string heightMapFileName;
	BYTE* heightData;

	int width;
	int depth;
};

#endif //! D3DHEIGHTMAP_H_
