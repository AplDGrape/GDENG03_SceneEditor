#pragma once
#include "EngineTime.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent;

class PhysicsSystem
{
public:
	PhysicsSystem();

	typedef std::string String;
	typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
	typedef std::vector <PhysicsComponent*> ComponentList;

	void registerComponent(PhysicsComponent* component);
	void unregisterComponent(PhysicsComponent* component);
	PhysicsComponent* findComponentByName(String name);
	ComponentList getAllComponents();

	void updateAllComponents();
	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

	~PhysicsSystem();
private:
	ComponentTable componentTable;
	ComponentList componentList;

	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;

	float ticks = 0.0f;
};