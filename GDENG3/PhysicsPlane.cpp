#include "PhysicsPlane.h"
#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

PhysicsPlane::PhysicsPlane(String name): Cube(name, PHYSICS_PLANE)
{
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.BASE_VERTEX_SHADER_NAME, &shaderdata.shaderByteCode, &shaderdata.sizeShader);

	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.01f, -0.5f),   Vector3D(1, 1, 1)},
		{Vector3D(-0.5f,  0.01f, -0.5f),   Vector3D(1, 1, 1)},
		{Vector3D( 0.5f,  0.01f, -0.5f),   Vector3D(1, 1, 1)},
		{Vector3D( 0.5f, -0.01f, -0.5f),   Vector3D(1, 1, 1)},
		//BACK FACE
		{Vector3D( 0.5f, -0.01f, 0.5f),    Vector3D(1, 1, 1)},
		{Vector3D( 0.5f,  0.01f, 0.5f),    Vector3D(1, 1, 1)},
		{Vector3D(-0.5f,  0.01f, 0.5f),    Vector3D(1, 1, 1)},
		{Vector3D(-0.5f, -0.01f, 0.5f),    Vector3D(1, 1, 1)}
	};

	this->vertex_buffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->vertex_buffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderdata.shaderByteCode, shaderdata.sizeShader);

	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
	
	this->index_buffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);
	this->index_buffer->load(index_list, size_index_list);

	constant cc;
	cc.time = 0;

	this->constant_buffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constant_buffer->load(&cc, sizeof(constant));

	this->setPosition(0.0f, -5.0f, 0.0f);
	this->setScale(33.5f, 0.2f, 35.5f);
	//this->setRotation(0.0f, 0.0f, 0.0f);
	this->ComputeLocalMatrix();

	this->attachComponent(new PhysicsComponent("PhysicsComponent", this));

	PhysicsComponent* component = (PhysicsComponent*)this->findComponentbyType(AComponent::ComponentType::Physics, "PhysicsComponent");
	component->getRigidBody()->setType(BodyType::KINEMATIC);

	this->vertex_shader = Shaderlibrary::getInstance()->getVertexShader(namesShader.BASE_VERTEX_SHADER_NAME);
	this->pixel_shader = Shaderlibrary::getInstance()->getPixelShader(namesShader.BASE_PIXEL_SHADER_NAME);
}

PhysicsPlane::~PhysicsPlane()
{
}
