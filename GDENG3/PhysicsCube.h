#pragma once
#include "Cube.h"
#include "PhysicsComponent.h"

class PhysicsCube: public Cube
{
public:
	PhysicsCube(String name);

	void awake() override;
	void draw(int width, int height) override;
	void update(float deltaTime) override;

	void saveEditState() override;
	void restoreEditState() override;

	~PhysicsCube();
private:
	PhysicsComponent* attachedComponent;
};