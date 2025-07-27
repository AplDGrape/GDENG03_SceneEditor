#pragma once
#include "ResourceManager.h"
#include "Texture.h"

#include <string>

class Texture;

class TextureManager: public ResourceManager
{
public:
	static TextureManager* getInstance();

	static void initialize();
	static void destroy();

	Texture* createTextureFromFile(const wchar_t* file_path);
private:
	static TextureManager* sharedInstance;
private:
	TextureManager();
	~TextureManager();
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
	std::unordered_map<std::wstring, Resource*> m_map_resources;
};

