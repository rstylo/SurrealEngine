#include "DxManager.h"



DxManager::DxManager()
{
}


DxManager::~DxManager()
{
	//clean vertexbuffers
	for (std::map< std::string, DxVertexBuffer* >::iterator it = vertexBuffers.begin(); it != vertexBuffers.end(); it++)
	{
		DeleteVertexBuffer(it->first);
	}
	vertexBuffers.clear();


	//clean textures
	for (std::map< std::string, DxTexture* >::iterator it = textures.begin(); it != textures.end(); it++)
	{
		DeleteTexture(it->first);
	}
	textures.clear();

	//clean meshes
	for (std::map< std::string, DxMesh* >::iterator it = meshes.begin(); it != meshes.end(); it++)
	{
		DeleteMesh(it->first);
	}
	meshes.clear();


	//clean heightmap
	for (std::map< std::string, DxHeightMap* >::iterator it = heightMaps.begin(); it != heightMaps.end(); it++)
	{
		DeleteHeightMap(it->first);
	}
	heightMaps.clear();


}

bool DxManager::AddTexture(DxTexture * texture)
{
	//! checks if resource already exists
	if (textures.find(texture->textureName) != textures.end())
		return false;

	textures[texture->textureName] = texture;
	return true;
}

DxTexture * DxManager::GetTexture(std::string textureName)
{
	if (textures.find(textureName) != textures.end())
		return textures.find(textureName)->second;

	return NULL;
}

bool DxManager::DeleteTexture(std::string textureName)
{
	
	
	if (textures.find(textureName) == textures.end())
		return false;

	DxTexture* item = textures.find(textureName)->second;
	if(item != NULL)
		if (item->texture != NULL)
		{
			item->texture->Release();
			item->texture = NULL;
		}
	delete item;
	item = NULL;

	
	
}

bool DxManager::AddMesh(DxMesh *mesh)
{
	if (meshes.find(mesh->meshPath) != meshes.end())
		return false;

	meshes[mesh->meshPath] = mesh;
	return true;
}

DxMesh * DxManager::GetMesh(std::string meshName)
{
	if (meshes.find(meshName) != meshes.end())
		return meshes.find(meshName)->second;

	return NULL;
}

bool DxManager::DeleteMesh(std::string meshName)
{
	if (meshes.find(meshName) == meshes.end())
		return false;

	DxMesh* item = meshes.find(meshName)->second;
	
	if (item != NULL)
	{
		if (item->materials != NULL)
			delete[] item->materials;

		if (item->textures)
		{
			for (DWORD i = 0; i < item->numOfMaterials; i++)
			{
				if (item->textures[i])
					item->textures[i]->Release();
			}
			delete[] item->textures;
		}

		if (item->mesh != NULL)
		{
			item->mesh->Release();
			item->mesh = NULL;
		}

		item->initialized = false;
		delete item;
		item = NULL;
	}

	return true;
}

bool DxManager::AddHeightMap(DxHeightMap *heightMap)
{
	if (heightMaps.find(heightMap->heightMapName) != heightMaps.end())
		return false;

	heightMaps[heightMap->heightMapName] = heightMap;
	return true;
}

DxHeightMap * DxManager::GetHeightMap(std::string heightMapName)
{
	if (heightMaps.find(heightMapName) != heightMaps.end())
		return heightMaps.find(heightMapName)->second;

	return NULL;
}

bool DxManager::DeleteHeightMap(std::string heightMapName)
{
	if (heightMaps.find(heightMapName) == heightMaps.end())
		return false;

	DxHeightMap* item = heightMaps.find(heightMapName)->second;
	if (item != NULL)
	{
		

		if (item->heightData != NULL)
		{
			delete item->heightData;
			item->heightData = NULL;
		}
		delete item;
		item = NULL;
	}


}

bool DxManager::AddVertexBuffer(DxVertexBuffer *vertexBuffer)
{
	if (vertexBuffers.find(vertexBuffer->name) != vertexBuffers.end())
		return false;

	vertexBuffers[vertexBuffer->name] = vertexBuffer;
	return true;
}

DxVertexBuffer * DxManager::GetVertexBuffer(std::string name)
{
	if (vertexBuffers.find(name) != vertexBuffers.end())
		return vertexBuffers.find(name)->second;

	return NULL;
}

bool DxManager::DeleteVertexBuffer(std::string name)
{
	if (vertexBuffers.find(name) == vertexBuffers.end())
		return false;

	DxVertexBuffer* item = vertexBuffers.find(name)->second;

	if (item != NULL)
	{
		

		if (item->vertexBuffer != NULL)
		{
			item->vertexBuffer->Release();
			item->vertexBuffer = NULL;

		}

		if (item->indexBuffer != NULL)
		{
			item->indexBuffer->Release();
			item->indexBuffer = NULL;

		}
		delete item;
		item = NULL;
	}

}
