#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "AGameObject.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, ComponentType::Physics, owner)
{
	// Whenever a new physics component is initialized. Register to physics system
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);

	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->getLocalScale();

	Transform transform;
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());

	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));	// Half extent
	SphereShape* shpereShape = physicsCommon->createSphereShape(1);
	CapsuleShape* capsuleShape = physicsCommon->createCapsuleShape(1, 1);

	this->rigidBody = physicsWorld->createRigidBody(transform);

	if(owner->getType() == AGameObject::CUBE)
	{
		this->rigidBody->addCollider(boxShape, transform);
	}
	else if(owner->getType() == AGameObject::SPHERE)
	{
		this->rigidBody->addCollider(shpereShape, transform);
	}
	else if (owner->getType() == AGameObject::CAPSULE)
	{
		this->rigidBody->addCollider(capsuleShape, transform);
	}
	else
	{
		this->rigidBody->addCollider(boxShape, transform);
	}
	
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setLocalMatrix(matrix);
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float Matrix[16];
	transform.getOpenGLMatrix(Matrix);

	this->getOwner()->setLocalMatrix(Matrix);
	//std::cout << "My component is updating: " << this->name << "\n";
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}

PhysicsComponent::~PhysicsComponent()
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
}