#include "PhysicsCube.h"
#include "Math.h"

PhysicsCube::PhysicsCube(String name): Cube(name, AGameObject::PHYSICS_CUBE)
{
	this->setPosition(Math::getRandom(0.1, 0.9), 6.0f, Math::getRandom(0.1, 0.9));
	this->setScale(1.5f, 1.5f, 1.5f);
	this->ComputeLocalMatrix();
	this->attachedComponent = new PhysicsComponent("Physics Component", this);
	this->attachComponent(this->attachedComponent);
}

void PhysicsCube::awake()
{
}

void PhysicsCube::draw(int width, int height)
{
	Cube::draw(width, height);
}

void PhysicsCube::update(float deltaTime)
{
	Cube::update(deltaTime);
}

void PhysicsCube::saveEditState()
{
	AGameObject::saveEditState();
}

void PhysicsCube::restoreEditState()
{
	AGameObject::restoreEditState();

	this->detachComponent(this->attachedComponent);
	delete this->attachedComponent;

	this->attachedComponent = new PhysicsComponent("PhysicsComponent_" + this->name, this);
	this->attachComponent(this->attachedComponent);
}

PhysicsCube::~PhysicsCube()
{
	Cube::~Cube();
}