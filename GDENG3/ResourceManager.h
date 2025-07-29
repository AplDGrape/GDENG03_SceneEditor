#pragma once
#include <unordered_map>
#include <string>
#include "Resource.h"
#include <iostream>

class ResourceManager
{
public:
	ResourceManager();

	Resource* createResourceFromFile(const wchar_t* file_path);

	virtual ~ResourceManager();
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) = 0;
	std::unordered_map<std::wstring, Resource*> m_map_resources;
};