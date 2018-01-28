#include "Terrain.h"

#include "D3DTexture.h"
#include "D3DVertexBuffer.h"
#include "D3dHeightMap.h"


Terrain::Terrain()
{
	//! initialises with transform position and rotation all set to origin point
	transform.SetPosition(Vector3(0, 0, 0));
	transform.SetRotation(Vector3(0, 0, 0));

	heightMap = new D3dHeightMap();
	texture = new D3DTexture();
	vertexBuffer = new D3DVertexBuffer();


	initialized = false;
}

Terrain::~Terrain()
{
	CleanUp();
}

void Terrain::SetMapAndTexture(std::string _heightMapFileName, std::string _textureName)
{
	//! sets terrains heightmap and texturename, and readies initialiazation before next draw routine
	heightMap->SetMapFileName(_heightMapFileName);
	texture->SetTextureName(_textureName);


	initialized = false;
}

void Terrain::Invalidate()
{
	//! reales vertex and index buffers + texture to free space
	initialized = false;
	CleanUp();
}

void Terrain::SetupMatrices(Renderer* renderer, Transform origin)
{
	transform.SetupMatrices(renderer, origin);
}

bool Terrain::Init(Renderer* renderer)
{
		//! initialises with one vertice *width*lenght of a given heightmap with a texture
		//! no normals or color included!!
		CleanUp();

		//y waarde ophalen uit de heightmap
		if (!heightMap->LoadBMP())
		{
			MessageBox(NULL, "failed loading heightmap", NULL, NULL);
			logger.Log("Failed loading heightmap", "Error");
			initialized = false;
			return false;

		}
		printf("succesfully loaded the heightmap... \n");
		logger.Log("Succesfully loaded the heightmap", "Info");


		int width = heightMap->GetWidth();
		int depth = heightMap->GetDepth();




		//! Creates terrain with
		const int numOfVertices = width * depth;						//! -1 vertices per quad
		const int numOfIndices = width * depth * 6;						//! -6 indicies per quad

		int primCount = width * depth * 2;										//! -2 triangles per quad
		int vertexCount = numOfVertices;

		xyzTextureVertex* vertices = new xyzTextureVertex[numOfVertices];	//! - vertex array
		WORD* indicies = new WORD[numOfIndices];							//! - index array

		int sizeOfVertices = numOfVertices * sizeof(xyzTextureVertex);		//! - sizeof the vertex array
		int sizeOfIndices = numOfIndices * sizeof(WORD);					//! - sizeof the indexarray

		int vCounter = 0;													//! - current index for inserting vertices
		int iCounter = 0;													//! - current index for inserting vertex-indecis

		D3DXVECTOR2 textureCords;											//! - texture coordinates (u,v)
		textureCords.x = 0;
		textureCords.y = 0;

		float uScale = 4 / width;											//! - texture scale
		float vScale = 4 / depth;

		byte* heightData = heightMap->GetHeightData();
		//! Iterate though x and z
		for (int x = 0; x < width; x++)
		{

			for (int z = 0; z < depth; z++)
			{
				//! - gets height for currentpoint from heightmap
				float height0 = (float)heightData[x * depth + z]; //! inline stament to check if outofbound


				//! - decides point for the to be drawn quad
				int p2 = vCounter;

				int p1 = (vCounter >= depth) ? vCounter - depth : p2;
				
				int p4 = (z + 1 < depth) ? vCounter + 1 : p2;

				int p3 = (z + 1 < depth && vCounter + 1 >= depth) ? vCounter + 1 - depth : p1;

				// - inserts index of vertex-array to create two triangles
				indicies[iCounter]     = p2;
				indicies[iCounter + 1] = p1;
				indicies[iCounter + 2] = p4;


				indicies[iCounter + 3] = p4;
				indicies[iCounter + 4]  = p1;
				indicies[iCounter + 5]  = p3;
				

				iCounter += 6;



				//! - creates current vertice on point x,z and inserts height data.
				vertices[vCounter] = { 0.0f + x, height0, 0.0f + z, textureCords.x, textureCords.y, 0x00800000 };
				vCounter++;

				if (textureCords.y > 0)
					textureCords.y = 0;
				else
					textureCords.y = 1;
			}

			if (textureCords.x > 0)
				textureCords.x = 0;
			else
				textureCords.x = 1;

			textureCords.y = 0;
		}

		//! decide which renderer to use
		if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
			LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();

			if (!vertexBuffer->Init(device, primCount, vertexCount, vertices, indicies, sizeOfVertices, sizeOfIndices))
				return false;

			if (!texture->Init(device))
				return false;

		//! returns true is succesful
		initialized = true;
		return true;
	}
}

void Terrain::Draw(Renderer* renderer)
{
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) 
	{
		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();

		if (vertexBuffer != NULL && device != NULL && texture != NULL && heightMap != NULL)
		{
			texture->Draw(device);
			vertexBuffer->Draw(device);
		}
	}

}



void Terrain::CleanUp()
{
	//! releases vertexbuffer and indexbuffer + texture
	if (vertexBuffer != NULL)
	{
		vertexBuffer->CleanUp();
	}

	if (texture != NULL)
	{
		texture->CleanUp();
	}

	if (heightMap != NULL)
	{
		heightMap->CleanUp();
	}
}

std::string Terrain::GetMapFileName()
{
	return heightMap->GetMapFileName();
}

std::string Terrain::GetTextureName()
{
	return texture->GetTextureName();
}

byte* Terrain::getHeightArray()
{

	return heightMap->GetHeightData();
}

int Terrain::getTerrainWidth()
{
	return heightMap->GetWidth();
}

int Terrain::getTerrainDepth()
{
	return heightMap->GetDepth();
}

bool Terrain::getInitialized()
{
	return initialized;
}
