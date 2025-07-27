#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "EngineTime.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "Matrix4x4.h"
#include "SceneCameraHandler.h"
#include "EngineTime.h"
#include "Shaderlibrary.h"
#include "Vector2D.h"

class Cube: public AGameObject
{
public:
	Cube(String name, AGameObject::PrimitiveType type);

	void update(float deltaTime) override;
	void draw(int width, int height) override;

	void setAnimSpeed(float speed);

	void saveEditState() override;
	void restoreEditState() override;
	void setTexturesVertexBuffer();
	
	~Cube();
protected:
	VertexBuffer* vertex_buffer;
	VertexBufferTextured* vertexbufferTextured;
	IndexBuffer* index_buffer;
	IndexBuffer* indexbufferTextured;
	ConstantBuffer* constant_buffer;
protected:
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float speed = 10.0f;
protected:
	ShaderNames namesShader;
	Shaderlibrary::ShaderData shaderdata;
	Shaderlibrary::ShaderData shaderdataTexture;
};