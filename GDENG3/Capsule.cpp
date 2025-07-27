#include "Capsule.h"

#include "AGameObject.h"
#include "Vector2D.h"
#include "AGameObject.h"
#include "PhysicsComponent.h"

Capsule::Capsule(String name): AGameObject(name, PrimitiveType::CAPSULE)
{
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.BASE_VERTEX_SHADER_NAME, &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.TEXTURED_VERTEX_SHADER_NAME, &shaderdataTexture.shaderByteCode, &shaderdataTexture.sizeShader);

	float Resolution = 5.5f;
	this->length = 1.5f;
	this->radius = 1.5f;

	Vector3D start = Vector3D(0.0f, 0.f, 0.0f);
	Vector3D end = Vector3D(1.0f, 1.0f, 1.0f);

	Vector3D step = (end - start) / Resolution;

	for (float i = 0.0f; i < Resolution; i++)
	{
		for (float j = 0.0f; j < Resolution; j++)
		{
			float u = i * step.m_x + start.m_x;
			float v = j * step.m_y + start.m_y;
			float un = 0.0f;
			float vn = 0.0f;

			if (i + 1.0f == Resolution)
			{
				un = end.m_x;
			}
			else
			{
				un = (i + 1.0f) * step.m_x + start.m_x;
			}

			if (j + 1.0f == Resolution)
			{
				vn = end.m_y;
			}
			else
			{
				vn = (j + 1.0f) * step.m_y + start.m_y;
			}

			int verticesStartIndex = this->Vertices.size();
			vertex vertex0 = { this->cylinder(u, v), Vector3D((float)i / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f)};
			vertex vertex1 = { this->cylinder(u, vn), Vector3D((float)i / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex vertex2 = { this->cylinder(un, v), Vector3D((float)i + 1.0f / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex vertex3 = { this->cylinder(un, vn), Vector3D((float)i + 1.0f / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };

			Vertex texVert0 = { this->cylinder(u, v), Vector2D((float)i / Resolution, (float)j / Resolution) };
			Vertex texVert1 = { this->cylinder(u, vn), Vector2D((float)i / Resolution, (float)j + 1.0f / Resolution) };
			Vertex texVert2 = { this->cylinder(un, v), Vector2D((float)i + 1.0f / Resolution, (float)j / Resolution) };
			Vertex texVert3 = { this->cylinder(un, vn), Vector2D((float)i + 1.0f / Resolution, (float)j / Resolution) };

			this->Vertices.push_back(vertex0);
			this->Vertices.push_back(vertex1);
			this->Vertices.push_back(vertex2);
			this->Vertices.push_back(vertex3);

			this->verticesTextured.push_back(texVert0);
			this->verticesTextured.push_back(texVert1);
			this->verticesTextured.push_back(texVert2);
			this->verticesTextured.push_back(texVert3);

			this->Indices.push_back(verticesStartIndex);
			this->Indices.push_back(verticesStartIndex + 2);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 3);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 2);

			verticesStartIndex = this->Vertices.size();
			vertex0 = { this->sphereStart(u, v), Vector3D((float)i / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex1 = { this->sphereStart(u, vn), Vector3D((float)i / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex2 = { this->sphereStart(un, v), Vector3D((float)i + 1.0f / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex3 = { this->sphereStart(un, vn), Vector3D((float)i + 1.0f / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };

			texVert0 = { this->sphereStart(u, v), Vector2D((float)i / Resolution, (float)j / Resolution) };
			texVert1 = { this->sphereStart(u, vn), Vector2D((float)i / Resolution, (float)j + 1.0f / Resolution) };
			texVert2 = { this->sphereStart(un, v), Vector2D((float)i + 1.0f / Resolution, (float)j / Resolution) };
			texVert3 = { this->sphereStart(un, vn), Vector2D((float)i + 1.0f / Resolution, (float)j / Resolution) };

			this->Vertices.push_back(vertex0);
			this->Vertices.push_back(vertex1);
			this->Vertices.push_back(vertex2);
			this->Vertices.push_back(vertex3);

			this->verticesTextured.push_back(texVert0);
			this->verticesTextured.push_back(texVert1);
			this->verticesTextured.push_back(texVert2);
			this->verticesTextured.push_back(texVert3);

			this->Indices.push_back(verticesStartIndex);
			this->Indices.push_back(verticesStartIndex + 2);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 3);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 2);

			verticesStartIndex = this->Vertices.size();
			vertex0 = { this->sphereEnd(u, v), Vector3D((float)i / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex1 = { this->sphereEnd(u, vn), Vector3D((float)i / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex2 = { this->sphereEnd(un, v), Vector3D((float)i + 1.0f / Resolution, (float)j / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };
			vertex3 = { this->sphereEnd(un, vn), Vector3D((float)i + 1.0f / Resolution, (float)j + 1.0f / Resolution, 1.0f), Vector3D(1.0f,1.0f,1.0f) };

			texVert0 = { this->sphereEnd(u, v), Vector2D((float)i / Resolution, (float)j / Resolution) };
			texVert1 = { this->sphereEnd(u, vn), Vector2D((float)i / Resolution, (float)j + 1.0f / Resolution) };
			texVert2 = { this->sphereEnd(un, v), Vector2D((float)i + 1.0f / Resolution, (float)j / Resolution) };
			texVert3 = { this->sphereEnd(un, vn), Vector2D((float)i + 1.0f / Resolution, (float)j / Resolution) };

			this->Vertices.push_back(vertex0);
			this->Vertices.push_back(vertex1);
			this->Vertices.push_back(vertex2);
			this->Vertices.push_back(vertex3);

			this->verticesTextured.push_back(texVert0);
			this->verticesTextured.push_back(texVert1);
			this->verticesTextured.push_back(texVert2);
			this->verticesTextured.push_back(texVert3);

			this->Indices.push_back(verticesStartIndex);
			this->Indices.push_back(verticesStartIndex + 2);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 3);
			this->Indices.push_back(verticesStartIndex + 1);
			this->Indices.push_back(verticesStartIndex + 2);
		}
	}
	
	this->vertex_buffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->vertex_buffer->load(&(this->Vertices[0]), sizeof(vertex), this->Vertices.size(), shaderdata.shaderByteCode, shaderdata.sizeShader);

	this->vertexbufferTextured = GraphicsEngine::getInstance()->createTexturedVertexBuffer();
	this->vertexbufferTextured->load(&(this->verticesTextured[0]), sizeof(Vertex), this->verticesTextured.size(), shaderdataTexture.shaderByteCode, shaderdataTexture.sizeShader);

	this->index_buffer = GraphicsEngine::getInstance()->createIndexBuffer();
	this->index_buffer->load(&(this->Indices[0]), this->Indices.size());

	constant cc;
	this->constant_buffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constant_buffer->load(&cc, sizeof(constant));
}

void Capsule::draw(int width, int height)
{
	constant cc;
	if (this->getObjectTexture() == NULL)
	{
		this->vertex_shader = Shaderlibrary::getInstance()->getVertexShader(namesShader.BASE_VERTEX_SHADER_NAME);
		this->pixel_shader = Shaderlibrary::getInstance()->getPixelShader(namesShader.BASE_PIXEL_SHADER_NAME);
	}
	else
	{
		this->vertex_shader = Shaderlibrary::getInstance()->getVertexShader(namesShader.TEXTURED_VERTEX_SHADER_NAME);
		this->pixel_shader = Shaderlibrary::getInstance()->getPixelShader(namesShader.TEXTURED_PIXEL_SHADER_NAME);
	}

	if (this->overrideMatrix)
	{
		cc.world = this->getLocalMatrix();
	}
	else
	{
		this->ComputeLocalMatrix();
		cc.world = this->getLocalMatrix();
	}

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.view = cameraMatrix;

	float aspectRatio = (float)width / (float)height;

	cc.projection.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	DeviceContext* device = GraphicsEngine::getInstance()->getImmediateDeviceContext();

	this->constant_buffer->update(device, &cc);

	device->setConstantBuffer(this->vertex_shader, this->constant_buffer);
	device->setConstantBuffer(this->pixel_shader, this->constant_buffer);

	device->setVertexShader(this->vertex_shader);
	device->setPixelShader(this->pixel_shader);

	if (this->getObjectTexture() == NULL)
	{
		device->setVertexBuffer(this->vertex_buffer);
		device->setIndexBuffer(this->index_buffer);

		device->drawIndexedTriangleList(this->index_buffer->getSizeIndexList(), 0, 0);
	}
	else
	{
		device->setTexture(this->vertex_shader, this->texture);
		device->setTexture(this->pixel_shader, this->texture);

		device->setVertexBufferTextured(this->vertexbufferTextured);
		device->setIndexBuffer(this->index_buffer);

		device->drawIndexedTriangleList(this->index_buffer->getSizeIndexList(), 0, 0);
	}
}

void Capsule::update(float deltaTime)
{
}

void Capsule::saveEditState() {
	PhysicsComponent* componentAttached = (PhysicsComponent*)this->findComponentbyType(AComponent::Physics, "Physics Component");
	if (componentAttached != nullptr)
	{
		AGameObject::saveEditState();
	}
}

void Capsule::restoreEditState()
{
	PhysicsComponent* componentAttached = (PhysicsComponent*)this->findComponentbyType(AComponent::Physics, "Physics Component");
	if (componentAttached != nullptr)
	{
		AGameObject::restoreEditState();
		this->detachComponent(componentAttached);
		componentAttached = new PhysicsComponent("Physics Component", this);
		this->attachComponent(componentAttached);
	}

}

Vector3D Capsule::cylinder(float u, float v)
{
	float pi = 3.1415926f;
	Vector3D x = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D z = Vector3D(0.0f, 0.0f, 1.0f);
	Vector3D capsuleEnd = Vector3D(0.0f, 0.0f, 0.0f);


	return capsuleEnd
		+ z * cosf(2.0f * pi * u) * this->radius
		+ x * sinf(2.0f * pi * u) * this->radius
		+ y * v * this->length;
}

Vector3D Capsule::sphereStart(float u, float v)
{
	float pi = 3.1415926f;
	Vector3D x = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D z = Vector3D(0.0f, 0.0f, 1.0f);
	Vector3D capsuleTop = Vector3D(0.0f, this->length, 0.0f);

	return capsuleTop
		+ z * cosf(2.0f * pi * u) * cosf((pi / 2.0f) * v) * this->radius
		+ x * sinf(2.0f * pi * u) * cosf((pi / 2.0f) * v) * this->radius
		+ y * sinf((pi / 2.0f) * v) * this->radius;
}

Vector3D Capsule::sphereEnd(float u, float v)
{
	float pi = 3.1415926f;
	Vector3D x = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D z = Vector3D(0.0f, 0.0f, 1.0f);
	Vector3D capsuleEnd = Vector3D(0.0f, 0.0f, 0.0f);

	return capsuleEnd
		+ z * cosf(2.0f * pi * u) * cosf((pi / 2.0f) * (v - 1)) * this->radius
		+ x * sinf(2.0f * pi * u) * cosf((pi / 2.0f) * (v - 1)) * this->radius
		+ y * sinf((pi / 2.0f) * (v - 1)) * this->radius;
}

Capsule::~Capsule()
{
	this->constant_buffer->release();
	this->index_buffer->release();
	this->vertex_buffer->release();
	AGameObject::~AGameObject();
}
