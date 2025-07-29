#pragma once
#include "ResourceManager.h"
#include "Mesh.h"

class Mesh;

class MeshManager: public ResourceManager
{
public:
	static MeshManager* getInstance();
	static void initialize();
	static void destroy();

	Mesh* createMeshFromFile(const wchar_t* file_path);
private:
	static MeshManager* sharedInstance;
private:
	MeshManager();
	~MeshManager();
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
	std::unordered_map<std::wstring, Resource*> m_map_resources;
};