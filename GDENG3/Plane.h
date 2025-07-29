#pragma once
#include "Cube.h"

class Plane : public Cube
{
public:
	Plane(String name);

	void draw(int width, int height) override;
	void setTexturesVertexBuffer();

	~Plane();
};