#pragma once
#include <d3d11.h>
#include "Resource.h"
#include "DeviceContext.h"

class DeviceContext;

class Texture: public Resource
{
public:
	Texture(const wchar_t* full_path);
	~Texture();
private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* shaderResView = nullptr;
private:
	friend class DeviceContext;
};