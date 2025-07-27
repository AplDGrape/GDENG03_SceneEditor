#pragma once
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "Matrix4x4.h"
#include "EngineTime.h"

class Rectangle
{
public:
	Rectangle();

	void draw();

	void setWindowSizeLength(float windowsizelength);
	void setWindowSizeHeight(float windowsizeheight);

	void setPosition(Vector3D Position);

	~Rectangle();
private:
	VertexBuffer* vertexbuffer;
	VertexShader* vertexshader;
	PixelShader* pixelshader;
	ConstantBuffer* constantbuffer;
private:
	unsigned long oldTime = 0;
	float deltaTime = 0;
	float angle = 0;

	float windowSizeHeight;
	float windowSizeLength;

	Vector3D position;
	Vector3D scale;

	float ticks = 0.0f;
	float cooldownrate = 10.0f;
	float rate = 0.0f;
	float speed = 0.0f;
	bool state = true;
};
