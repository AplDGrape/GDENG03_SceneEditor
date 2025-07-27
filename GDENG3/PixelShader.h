#pragma once
#include <d3d11.h>
#include <iostream>
#include "GraphicsEngine.h"

class DeviceContext;
class GraphicsEngine;

class PixelShader
{
public:
	PixelShader();
	void release();
	~PixelShader();
private:
	bool init(const void* shader_byte, size_t byte_code_size);
private:
	ID3D11PixelShader* m_ps;
private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};