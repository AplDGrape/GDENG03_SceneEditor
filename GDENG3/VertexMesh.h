#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	VertexMesh()
	{
		this->m_position = Vector3D(0.0f, 0.0f, 0.0f);
		this->m_texcoord = Vector2D(0.0f, 0.0f);
	}
	VertexMesh(Vector3D position, Vector2D texcoord)
	{
		this->m_position = position;
		this->m_texcoord = texcoord;
	}
	VertexMesh(const VertexMesh& vertex)
	{
		this->m_position = vertex.m_position;
		this->m_texcoord = vertex.m_texcoord;
	}
	~VertexMesh()
	{

	}
public:
	Vector3D m_position;
	Vector2D m_texcoord;
};