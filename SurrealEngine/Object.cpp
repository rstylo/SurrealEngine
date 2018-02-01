#include "Object.h"
#include "Renderer.h"


Object::Object(std::string _objectName)
	: Resource(), initialised(false)
{
	objectName = _objectName;
	textureName = "texture1.jpg";

	id = reinterpret_cast<uint32_t>(this);
}


Object::~Object()
{
}

void Object::CleanUp(Renderer* renderer)
{
	if (renderer != NULL)
	{
		renderer->UnLoadTexture(textureName);
		renderer->UnLoadVertices(std::to_string(id));
	}

}

bool Object::Init(Renderer* renderer)
{

	if (initialised == false)
	{
		CleanUp(renderer);

		if (!renderer->LoadTexture(textureName))
		{
			MessageBox(NULL, "failed loading object texture", NULL, NULL);
			return false;
		}

		const int numOfVertices = 8;										//8 vertices voor een cube
		const int numOfIndices = 6 * 6;										//6 indicies per quad

		primCount = 6 * 2;													//2 triangles per quad
		vertexCount = numOfVertices;


		int sizeOfVertices = numOfVertices * sizeof(xyzTextureVertex);			//sizeof the vertex array
		int sizeOfIndices = numOfIndices * sizeof(WORD);					//sizeof the indexarray


		//! init cube vertices
		xyzTextureVertex* vertices = new xyzTextureVertex[numOfVertices] //vertex array
		{
			{ 0.0f, 0.0f, 0.0f, 0, 0, 0x00800000 },        //0
			{ 1.0f, 0.0f, 0.0f, 1, 0, 0x00800000 },        //1
			{ 0.0f, 1.0f, 0.0f, 0, 1, 0x00800000 },        //2
			{ 1.0f, 1.0f, 0.0f, 1, 1, 0x00800000 },        //3

			{ 0.0f, 0.0f, 1.0f, 1, 1, 0x00800000 },        //4
			{ 1.0f, 0.0f, 1.0f, 0, 1 , 0x00800000 },        //5
			{ 0.0f, 1.0f, 1.0f, 1, 0, 0x00800000 },        //6
			{ 1.0f, 1.0f, 1.0f, 0, 0, 0x00800000 },        //7
		};

		WORD indicies[numOfIndices] =
		{

			//front face
			0, 1, 2,
			2, 1, 3,
			//back face
			4, 5, 6,
			6, 5, 7,
			//rightface
			1, 5, 3,
			3, 5, 7,
			//left face
			4, 0, 6,
			6, 0, 2,
			//top face
			4, 5, 0,
			0, 5, 1,
			//bottom face
			2, 3, 6,
			6, 3, 7
		};


		if (!renderer->LoadIndexedVertices(std::to_string(id), primCount, vertexCount, vertices, indicies, sizeOfVertices, sizeOfIndices))
		{
			MessageBox(NULL, "failed loading object dx buffers", NULL, NULL);
			return false;
		}

		initialised = true;
	}
	return true;

}

void Object::Draw(Renderer* renderer)
{
	if (renderer != NULL && initialised == true)
	{

		renderer->DrawTexture(textureName);
		renderer->DrawVertices(std::to_string(id));
	}
}

std::string Object::GetObjectName()
{
	return objectName;
}

void Object::SetTexture(std::string _textureName)
{
	textureName = _textureName;
}
