#pragma once
#include <string>
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include <vector>

#include "VertexShader.h"
#include "PixelShader.h"

#include "Texture.h"
#include "AComponent.h"

#include "reactphysics3d/reactphysics3d.h"

using namespace reactphysics3d;
class EditorAction;
class AComponent;

class AGameObject
{
public:
	enum PrimitiveType 
	{
		CAMERA,
		TEXTURED_CUBE,
		CUBE,
		PLANE,
		SPHERE,
		CAPSULE,
		PHYSICS_CUBE,
		PHYSICS_PLANE,
		OBJ,
		CYLINDER,
		BUNNY_OBJ
	};

	struct AQuaternion 
	{
		float w = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color1;
	};

	struct Vertex
	{
		Vector3D position;
		Vector2D texCoord;
	};

	_declspec(align(16)) struct constant
	{
		Matrix4x4 world;
		Matrix4x4 view;
		Matrix4x4 projection;
		unsigned int time;
	};

	typedef std::string String;
	typedef std::vector<AComponent*> ComponentList;
public:
	AGameObject(String name, PrimitiveType type);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setLocalMatrix(float matrix[16]);
	Matrix4x4 getLocalMatrix();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationz(float z);
	Vector3D getLocalRotation();

	void enable();
	void disable();
	bool getStatus();
public:
	String getName();
	void setName(String name);
	PrimitiveType getType();
	void ComputeLocalMatrix();
	float* getPhysicsLocalMatrix();

	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);
public:
	AComponent* findComponentByName(String name);
	AComponent* findComponentbyType(AComponent::ComponentType type, String name);
	ComponentList getComponentsOfType(AComponent::ComponentType type);

	void setObjectTexture(Texture* texture);
	Texture* getObjectTexture();
	void setTextureFlag();
	bool textureFlag();

	virtual void saveEditState();
	virtual void restoreEditState();
protected:
	VertexShader* vertex_shader;
	PixelShader* pixel_shader;

	Vector3D Position;
	Vector3D Scale;
	Vector3D Rotation;
protected:
	String name;
	bool enabled = true;
	bool isTextured = false;

	Texture* texture;
	Matrix4x4 LocalMatrix;

	Vector3D rotation;

	Matrix4x4 Summation;
	Matrix4x4 translate;
	Matrix4x4 ScaleMatrix;

	Matrix4x4 RotationZ;
	Matrix4x4 RotationF;
	Matrix4x4 RotationGl;
	Matrix4x4 RotationMatrix;
	Matrix4x4 RotationTotal;

	ComponentList componentList;
	bool overrideMatrix = false;
	AQuaternion orientation;

	PrimitiveType objectType;

	virtual void awake();
private:
	EditorAction* lastEditState = NULL;
};
