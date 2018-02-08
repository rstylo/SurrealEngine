/*! \file  Terrain.h
	\brief this class is used to draw and move the terrain
*/


#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <iostream>

#include <list>
#include <string>
#include <map>

#include "Transform.h"

typedef unsigned char byte;			// 0 - 255



class Renderer;

class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	virtual void SetMapAndTexture(std::string heightMapFileName, std::string _textureName);		//! change heightmap and texture
	virtual bool Init(Renderer*);																//! initialise
	virtual void Invalidate(Renderer*);															//! release the vertex buffer and indexBuffer to free space


	virtual void SetupMatrices(Renderer*, Transform);											//! setup position in which terrain is to be drawn
	//virtual bool InitWithColor(Renderer*);
	virtual void Draw(Renderer*);																

	virtual std::string GetMapFileName();														//! returns heightmaps name		
	virtual std::string GetTextureName();														//! returns texture's name

	virtual byte* getHeightArray();																//! returns height map in unsigned char
	virtual int getTerrainWidth();																//! returns terrain width
	virtual int getTerrainDepth();																//! returns terrain depth
	virtual bool getInitialized();																//! returns true if terrain is initialised

	Transform transform;
private:

	virtual void CleanUp(Renderer*);

	bool initialized;

	std::string mapFileName;
	std::string textureName;

	int width;
	int depth;
	byte* heightData;

	uint32_t id;

};


#endif // !TERRAIN_H_
