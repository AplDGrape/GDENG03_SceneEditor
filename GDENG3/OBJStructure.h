#pragma once
#include "AGameObject.h"
#include "Texture.h"
#include "Mesh.h"
#include "SceneCameraHandler.h"

class OBJStructure: public AGameObject
{
public:
	OBJStructure(Mesh* mesh, Texture* texture, String name);

	void draw(int width, int height) override;
	void update(float deltaTime) override;

	~OBJStructure();
private:
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float oldDelta = 0.0f;
	float newDelta = 0.0f;
	float speed = 10.0f;
	float rate = 3.14;
private:
	Vector3D rotation;

	Matrix4x4 Summation;
	Matrix4x4 translate;
	Matrix4x4 Scale;

	Matrix4x4 RotationZ;
	Matrix4x4 RotationF;
	Matrix4x4 RotationGl;
	Matrix4x4 Rotation;

	Matrix4x4 RotationTotal;
private:
	ShaderNames namesShader;
	Mesh* meshModel;
	ConstantBuffer* constantbuffer;
	Texture* textureModel;
};