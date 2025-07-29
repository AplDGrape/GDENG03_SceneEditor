#pragma once
#include "PhysicsSystem.h"

class PhysicsSystem;

class BaseComponentSystem
{
public:
	typedef std::string String;

	static BaseComponentSystem* getInstance();

	static void initialize();
	static void destroy();

	PhysicsSystem* getPhysicsSystem();

private:
	BaseComponentSystem();
	
	BaseComponentSystem(BaseComponentSystem const&) {};				// Copy constructor is private
	BaseComponentSystem& operator=(BaseComponentSystem const&) {};	// Assignment operator is private
	static BaseComponentSystem* sharedInstance;

	PhysicsSystem* physicsSystem;

	~BaseComponentSystem();
};