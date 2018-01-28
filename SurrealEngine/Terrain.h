/*! \file  Terrain.h
	\brief this class is used to draw and move the terrain
*/


#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <iostream>
#include <map>
#include <list>
#include <string>

#include "Transform.h"

class D3DTexture;
class D3DVertexBuffer;
class D3dHeightMap;

class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	virtual void SetMapAndTexture(std::string heightMapFileName, std::string _textureName);		//! change heightmap and texture
	virtual bool Init(Renderer*);																//! initialise
	virtual void Invalidate();																	//! release the vertex buffer and indexBuffer to free space


	virtual void SetupMatrices(Renderer*, Transform);											//! setup position in which terrain is to be drawn
	//virtual bool InitWithColor(Renderer*);
	virtual void Draw(Renderer*);																

	virtual std::string GetMapFileName();														
	virtual std::string GetTextureName();

	virtual byte* getHeightArray();
	virtual int getTerrainWidth();
	virtual int getTerrainDepth();
	virtual bool getInitialized();

	Transform transform;
private:

	virtual void CleanUp();

	bool initialized;

	D3DTexture* texture;
	D3DVertexBuffer* vertexBuffer;
	D3dHeightMap* heightMap;

	Logger logger;


};


#endif // !TERRAIN_H_
