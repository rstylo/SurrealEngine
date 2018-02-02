#include "Skybox.h"
#include "Renderer.h"



Skybox::Skybox()
{
	id = reinterpret_cast<uint32_t>(this);			//cast de classe naar een uint32_t, sinds klassen al unique zijn zal dit ervoor zorgen dat elke entity een eigen positive int getal als id heeft
}

Skybox::~Skybox()
{

}

bool Skybox::Init(Renderer* renderer)
{
	//! initialise skyboxes vertex/index buffers if texture is set

	float height = 0;
	float width = 0;

	if (!renderer->LoadTexture(textureName))
	{
		MessageBox(NULL, "failed loading skybox textures", NULL, NULL);
		return false;
	}

	height = renderer->GetTextureHeight(textureName);
	width = renderer->GetTextureWidth(textureName);

	int size = 100;

	const int numOfVertices = 14;										//
	const int numOfIndices = 6 * 6;										//! - 6 indicies per quad

	xyzTextureVertex* vertices = new xyzTextureVertex[numOfVertices];	//! - vertex array


	int sizeOfVertices = numOfVertices * sizeof(xyzTextureVertex);		//! - sizeof the vertex array
	int sizeOfIndices = numOfIndices * sizeof(WORD);					//! - sizeof the indexarray

	

	vertices[0].position = Vector3(+size, +size,-size);
	vertices[1].position = Vector3(+size,-size,-size);
	vertices[2].position = Vector3(-size, +size,-size);
	vertices[3].position = Vector3(-size,-size,-size);
	vertices[4].position = Vector3(-size, +size, +size);
	vertices[5].position = Vector3(-size,-size, +size);
	vertices[6].position = Vector3(+size, +size, +size);
	vertices[7].position = Vector3(+size,-size, +size);

	vertices[8].position = Vector3(+size,-size,-size);		//vertex 1 // top
	vertices[9].position = Vector3(+size,-size, +size);		//vertex 7

	vertices[10].position = Vector3(+size, +size,-size);	//vertex 0 // bottom
	vertices[11].position = Vector3(+size, +size, +size);	//vertex 6

	vertices[12].position = Vector3(+size, +size,-size);	//vertex 0
	vertices[13].position = Vector3(+size,-size,-size);		//vertex 1

	vertices[0].tu = 0.00f;
	vertices[0].tv = (float)1 / 3 + 1 / height;
	vertices[1].tu = 0.00f;
	vertices[1].tv = (float)2 / 3 - 1 / height;
	vertices[2].tu = (float)1 / 4 + 1 / width;
	vertices[2].tv = (float)1 / 3 + 1 / height;
	vertices[3].tu = (float)1 / 4 + 1 / width;
	vertices[3].tv = (float)2 / 3 - 1 / height;
	vertices[4].tu = (float)2 / 4 - 1 / width;
	vertices[4].tv = (float)1 / 3 + 1 / height;
	vertices[5].tu = (float)2 / 4 - 1 / width;
	vertices[5].tv = (float)2 / 3 - 1 / height;
	vertices[6].tu = 0.75f;
	vertices[6].tv = (float)1 / 3 + 1 / height;
	vertices[7].tu = 0.75f;
	vertices[7].tv = (float)2 / 3 - 1 / height;

	vertices[12].tu = 1.00f;						// vertex 0 with other texture coordinate
	vertices[12].tv = (float)1 / 3 + 1 / height;
	vertices[13].tu = 1.00f;						// vertex 1 with other texture coordinate
	vertices[13].tv = (float)2 / 3 - 1 / height;

	vertices[8].tu = (float)1 / 4 + 1 / width;		// bottom 
	vertices[8].tv = 1.00f - 1 / height;			// vertex 1 with other texture coordinate
	vertices[9].tu = (float)2 / 4 - 1 / width;
	vertices[9].tv = 1.00f - 1 / height;			// vertex 7 with other texture coordinate

	vertices[10].tu = (float)1 / 4 + 1 / width;		// top
	vertices[10].tv = 1 / height;					// vertex 0 with other texture coordinate
	vertices[11].tu = (float)2 / 4 - 1 / width;
	vertices[11].tv = (float)1 / height;			// vertex 6 with other texture coordinate

	WORD* indicies = new WORD[numOfIndices]			//! - index array
	{
		0, 1, 2,    // side 1
		2, 1, 3,

		2, 3, 4,	// side 2
		4, 3, 5,

		4, 5, 6,	// side 3
		6, 5, 7,

		12, 13, 6,	// side 4
		6, 13, 7,

		3, 8, 9,	// side bottom
		3, 5, 9,

		2, 10, 4,	// side top
		4, 10, 11,
	};
	

	if (!renderer->LoadIndexedVertices(std::to_string(id), numOfIndices/3, numOfVertices, vertices, indicies, sizeOfVertices, sizeOfIndices))
	{
		MessageBox(NULL, "failed loading skybox vertices", NULL, NULL);
		return false;
	}
	return true;
}
void Skybox::Update(Vector3 _position)
{
	//! updates skybox position to given vector
	transform.SetPosition(Vector3(_position.x, _position.y, _position.z));
	transform.SetRotation(Vector3(0, 0, 0));
}

void Skybox::Invalidate(Renderer* renderer)
{

	//! releases texture data and vertex/index buffers to free space
	if (renderer != NULL)
	{
		renderer->UnLoadTexture(textureName);
		renderer->UnLoadVertices(std::to_string(id));
	}

}


void Skybox::SetupMatrices(Renderer* renderer, Transform origin)
{
	//!change skyboxe's position
	transform.SetupMatricesRotate(renderer, origin.GetRotation());
}

void Skybox::Draw(Renderer* renderer)
{
	//! draws skybox if initialised
	if(renderer != NULL)
	{
		renderer->DrawTexture(textureName);
		renderer->DrawVerticesBackground(std::to_string(id));
	}
}

void Skybox::SetTexture(std::string _textureName)
{
	//! set the skybox texture
	textureName = _textureName;
}

std::string Skybox::GetTexture()
{
	//! returns skybox's texturename
	return textureName;
}