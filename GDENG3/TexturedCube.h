#pragma once
#include "Cube.h"
#include "Vector2D.h"
#include "Texture.h"
#include "TextureManager.h"
#include "VertexBufferTextured.h"
#include "Texture.h"

class TexturedCube: public Cube
{
public:
	TexturedCube(String name);

	void draw(int width, int height) override;
	void update(float deltaTime) override;

	~TexturedCube();
private:
	VertexBufferTextured* vertexbufferTextured;
	IndexBuffer* index_Buffer;
	ConstantBuffer* constant_Buffer;
};