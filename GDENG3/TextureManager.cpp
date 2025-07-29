#include "TextureManager.h"
#include "Texture.h"

#include <filesystem>
#include <iostream>

TextureManager* TextureManager::sharedInstance = NULL;

TextureManager::TextureManager(): ResourceManager()
{
}

Texture* TextureManager::createTextureFromFile(const wchar_t* file_path)
{
	std::wstring full_path = std::filesystem::absolute(file_path);
	if(this->m_map_resources[full_path] == NULL)this->m_map_resources[full_path] = this->createResourceFromFileConcrete(file_path);

	return (Texture*)this->m_map_resources[full_path];
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Texture* tex = nullptr;

	try
	{
		tex = new Texture(file_path);
	}
	catch (...) {}

	return tex;
}

TextureManager* TextureManager::getInstance()
{
	return sharedInstance;
}

void TextureManager::initialize()
{
	sharedInstance = new TextureManager();
}

void TextureManager::destroy()
{
	delete sharedInstance;
}

TextureManager::~TextureManager()
{
}