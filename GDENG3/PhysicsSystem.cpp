#include "PhysicsSystem.h"
#include "PhysicsComponent.h"

PhysicsSystem::PhysicsSystem()
{
	// Create the physics engine and world
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings worldSeting;

	worldSeting.defaultVelocitySolverNbIterations = 50;
	worldSeting.gravity = Vector3(0, -9.81, 0);

	this->physicsWorld = this->physicsCommon->createPhysicsWorld(worldSeting);
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	this->componentList.push_back(component);
	this->componentTable[component->getName()] = component;
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	this->componentTable.erase(component->getName());
	int index = -1;

	for(int i = 0; i < this->componentList.size(); i++)
	{
		if(this->componentList[i]->getName() == component->getName())
		{
			index = i;
			this->componentList.erase(this->componentList.begin() + index);
			break;
		}
	}
}

PhysicsComponent* PhysicsSystem::findComponentByName(String name)
{
	return this->componentTable.at(name);
}

PhysicsSystem::ComponentList PhysicsSystem::getAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::updateAllComponents()
{

	if(EngineTime::getDeltaTime() > 0.0f)
	{
		this->physicsWorld->update(EngineTime::getDeltaTime());

		for (int i = 0; i < this->componentList.size(); i++)
		{
			this->componentList[i]->perform(EngineTime::getDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}

PhysicsSystem::~PhysicsSystem()
{
	this->componentList.clear();
	this->componentTable.clear();

	this->physicsCommon = nullptr;
	this->physicsWorld = nullptr;
}