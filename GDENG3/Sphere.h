#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "VertexBufferTextured.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "SceneCameraHandler.h"
#include "Shaderlibrary.h"

class Sphere: public AGameObject
{
public:
	Sphere(String name);
	~Sphere();

	void draw(int width, int height) override;
	void update(float deltaTime) override;

	void saveEditState() override;
	void restoreEditState() override;
private:
	VertexBuffer* verterbuffer;
	VertexBufferTextured* verterBufferTextured;
	IndexBuffer* indexbuffer;
	ConstantBuffer* constantbuffer;
private:
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float speed = 10.0f;
private:
	std::vector<vertex> vertices;
	std::vector<Vertex> verticesTextured;
	std::vector<unsigned int> indices;
private:
	ShaderNames namesShader;
	Shaderlibrary::ShaderData shaderdata;
	Shaderlibrary::ShaderData shaderdataTexture;
};
