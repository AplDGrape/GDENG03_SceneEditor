#pragma once
#include "Resource.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferTextured.h"

#include "Shaderlibrary.h"

class DeviceContext;

class Mesh: public Resource
{
public:
	Mesh(const wchar_t* full_path);
	
	VertexBufferTextured* getVertexBuffer();
	IndexBuffer* getIndexBuffer();

	~Mesh();
private:
	Shaderlibrary::ShaderData dataShader;
	ShaderNames names;

	VertexBufferTextured* vertexBuffer;
	IndexBuffer* indexBuffer;
private:
	friend class DeviceContext;
};