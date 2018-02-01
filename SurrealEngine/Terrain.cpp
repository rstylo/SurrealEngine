#include "Terrain.h"
#include "DirectXRenderer.h"

Terrain::Terrain()
{
	//! initialises with transform position and rotation all set to origin point
	transform.SetPosition(Vector3(0, 0, 0));
	transform.SetRotation(Vector3(0, 0, 0));

	id = reinterpret_cast<uint32_t>(this);			//cast de classe naar een uint32_t, sinds klassen al unique zijn zal dit ervoor zorgen dat elke entity een eigen positive int getal als id heeft


	initialized = false;
}

Terrain::~Terrain()
{
}

void Terrain::SetMapAndTexture(std::string _heightMapFileName, std::string _textureName)
{
	//! sets terrains heightmap and texturename, and readies initialiazation before next draw routine
	mapFileName = _heightMapFileName;
	textureName = _textureName;


	initialized = false;
}

void Terrain::Invalidate(Renderer* renderer)
{
	//! reales vertex and index buffers + texture to free space
	initialized = false;
	CleanUp(renderer);
}

void Terrain::SetupMatrices(Renderer* renderer, Transform origin)
{
	transform.SetupMatrices(renderer, origin);
}

bool Terrain::Init(Renderer* renderer)
{
	width = 0;
	depth = 0;
	heightData = 0;

	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
	{
		//! initialises with one vertice *width*lenght of a given heightmap with a texture
		//! no normals or color included!!
		CleanUp(renderer);

		//y waarde ophalen uit de heightmap
		if (!dxrenderer->LoadHeightMapWithBmp(mapFileName))
		{
			MessageBox(NULL, "failed loading heightmap", NULL, NULL);
			initialized = false;
			return false;

		}
		printf("succesfully loaded the heightmap... \n");


		if (!dxrenderer->LoadTexture(textureName))
		{
			MessageBox(NULL, "failed loading terrain texture", NULL, NULL);
			initialized = false;
			return false;

		}

		width = dxrenderer->GetHeightMapWidth(mapFileName);
		depth = dxrenderer->GetHeightMapDepth(mapFileName);
		heightData = dxrenderer->GetHeightData(mapFileName);
	}
		




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
		
		if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
		{
			if (!dxrenderer->LoadIndexedVertices(std::to_string(id), primCount, vertexCount, vertices, indicies, sizeOfVertices, sizeOfIndices))
			{
				MessageBox(NULL, "failed loading terrain dx buffers", NULL, NULL);
				initialized = false;
				return false;

			}
		}

		//! returns true is succesful
		initialized = true;
		return true;
}

void Terrain::Draw(Renderer* renderer)
{
	if (initialized == true && renderer != NULL)
		if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
		{
			dxrenderer->DrawTexture(textureName);
			dxrenderer->DrawVertices(std::to_string(id));
		}

}



void Terrain::CleanUp(Renderer* renderer)
{
	if (initialized == true && renderer != NULL)
		if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
		{
			dxrenderer->UnLoadHeightMap(mapFileName);
			dxrenderer->UnLoadTexture(textureName);
			dxrenderer->UnLoadVertices(std::to_string(id));
		}
}

std::string Terrain::GetMapFileName()
{
	return mapFileName;
}

std::string Terrain::GetTextureName()
{
	return textureName;
}

byte* Terrain::getHeightArray()
{

	return heightData;
}

int Terrain::getTerrainWidth()
{
	return width;
}

int Terrain::getTerrainDepth()
{
	return depth;
}

bool Terrain::getInitialized()
{
	return initialized;
}
