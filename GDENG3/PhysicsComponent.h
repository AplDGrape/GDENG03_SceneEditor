#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(String name, AGameObject* owner);
	
	// Executes physics system per frame
	void perform(float deltaTime) override;

	RigidBody* getRigidBody();

	~PhysicsComponent();
private:
	float mass = 1000.0f; // In kilograms
	RigidBody* rigidBody;
};