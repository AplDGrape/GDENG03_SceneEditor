#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "SceneCameraHandler.h"
#include "Shaderlibrary.h"

class Capsule : public AGameObject
{
public:
	Capsule(String name);

	void draw(int width, int height) override;
	void update(float deltaTime) override;

	Vector3D cylinder(float u, float v);
	Vector3D sphereStart(float u, float v);
	Vector3D sphereEnd(float u, float v);

	void saveEditState() override;
	void restoreEditState() override;

	~Capsule();
private:
	VertexBuffer* vertex_buffer;
	VertexBufferTextured* vertexbufferTextured;
	IndexBuffer* index_buffer;
	ConstantBuffer* constant_buffer;
private:
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float speed = 10.0f;

	std::vector<vertex> Vertices;
	std::vector<Vertex> verticesTextured;
	std::vector<unsigned int> Indices;
	std::vector<Vector3D> CircleVertices;

	int BaseCenterIndex;
	int TopCenterIndex;

	float length;
	float radius;
private:
	ShaderNames namesShader;
	Shaderlibrary::ShaderData shaderdata;
	Shaderlibrary::ShaderData shaderdataTexture;
};