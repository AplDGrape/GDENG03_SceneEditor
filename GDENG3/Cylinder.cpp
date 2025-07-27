#include "Cylinder.h"
#include "PhysicsComponent.h"

Cylinder::Cylinder(String name): AGameObject(name, PrimitiveType::CYLINDER)
{
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.BASE_VERTEX_SHADER_NAME, &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.TEXTURED_VERTEX_SHADER_NAME, &shaderdataTexture.shaderByteCode, &shaderdataTexture.sizeShader);

	float radius = 1.5f;
	int sectorCount = 12;
	float height = 1.5f;
	
	float pi = 3.1415926f;
	float sectorStep = 2 * pi / (float)sectorCount;
	float sectorAngle;

	for(int i = 0; i <= sectorCount; i++)
	{
		sectorAngle = i * sectorStep;
		Vector3D vector = Vector3D(sinf(sectorAngle), 0.0f, cosf(sectorAngle));
		this->CircleVertices.push_back(vector);
	}

	for(int i = 0; i < 2; i++)
	{
		float h = -height / 2.0f + i * height;
		int k = 0;
		float t = 1.0f - i;

		for(int j = 0; j <= sectorCount; j++)
		{
			Vector3D UnitVertex = this->CircleVertices[k];

			vertex Vertex = { Vector3D(UnitVertex.m_x * radius, h, UnitVertex.m_z * radius), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };
			struct Vertex TextureVertex = { Vector3D(UnitVertex.m_x * radius, h, UnitVertex.m_z * radius), Vector2D((float)j / sectorCount, t) };
			this->Vertices.push_back(Vertex);
			this->verticesTextured.push_back(TextureVertex);

			k++;
		}
	}

	this->BaseCenterIndex = this->Vertices.size();
	this->TopCenterIndex = this->BaseCenterIndex + sectorCount + 1;

	for(int i = 0; i < 2; i++)
	{
		float h = -height / 2.0f + i * height;
		vertex Vertex = { Vector3D(0.0f, h, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };
		this->Vertices.push_back(Vertex);
		int k = 0;

		for(int j = 0; j < sectorCount; j++)
		{
			Vector3D unitVertex = this->CircleVertices[k];

			vertex Vertex = { Vector3D(unitVertex.m_x * radius, h, unitVertex.m_z * radius),
			Vector3D(1, 1, 1), Vector3D(1, 1, 1) };

			struct Vertex TextureVertex = { Vector3D(unitVertex.m_x * radius, h, unitVertex.m_z * radius),
			Vector2D(-unitVertex.m_x * 0.5f + 0.5f, -unitVertex.m_y * 0.5f + 0.5f)};

			this->Vertices.push_back(Vertex);
			this->verticesTextured.push_back(TextureVertex);

			k++;
		}
	}

	this->vertexbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->vertexbuffer->load(&(this->Vertices[0]), sizeof(vertex), this->Vertices.size(), shaderdata.shaderByteCode, shaderdata.sizeShader);

	this->vertexBufferTextured = GraphicsEngine::getInstance()->createTexturedVertexBuffer();
	this->vertexBufferTextured->load(&(this->verticesTextured[0]), sizeof(struct Vertex), this->verticesTextured.size(), shaderdataTexture.shaderByteCode, shaderdataTexture.sizeShader);

	int k1 = 0;
	int k2 = sectorCount + 1;

	for (int i = 0; i < sectorCount; i++)
	{
		this->Indices.push_back(k1);
		this->Indices.push_back(k1 + 1);
		this->Indices.push_back(k2);

		this->Indices.push_back(k2);
		this->Indices.push_back(k1 + 1);
		this->Indices.push_back(k2 + 1);

		k1++;
		k2++;
	}

	int k = this->BaseCenterIndex + 1;

	for (int i = 0; i < sectorCount; i++)
	{
		if (i < sectorCount - 1)
		{
			this->Indices.push_back(this->BaseCenterIndex);
			this->Indices.push_back(k + 1);
			this->Indices.push_back(k);
		}
		else
		{
			this->Indices.push_back(this->BaseCenterIndex);
			this->Indices.push_back(this->BaseCenterIndex + 1);
			this->Indices.push_back(k);
		}

		k++;
	}

	k = this->TopCenterIndex + 1;

	for (int i = 0; i < sectorCount; i++)
	{
		if (i < sectorCount - 1)
		{
			this->Indices.push_back(this->TopCenterIndex);
			this->Indices.push_back(k);
			this->Indices.push_back(k + 1);
		}
		else
		{
			this->Indices.push_back(this->TopCenterIndex);
			this->Indices.push_back(k);
			this->Indices.push_back(this->TopCenterIndex + 1);
		}

		k++;
	}

	this->indexbuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	this->indexbuffer->load(&(this->Indices[0]), this->Indices.size());

	constant cc;

	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));
}

void Cylinder::draw(int width, int height)
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

	this->constantbuffer->update(device, &cc);

	device->setConstantBuffer(this->vertex_shader, this->constantbuffer);
	device->setConstantBuffer(this->pixel_shader, this->constantbuffer);

	device->setVertexShader(this->vertex_shader);
	device->setPixelShader(this->pixel_shader);

	if (this->getObjectTexture() == NULL)
	{
		device->setVertexBuffer(this->vertexbuffer);
		device->setIndexBuffer(this->indexbuffer);

		device->drawIndexedTriangleList(this->indexbuffer->getSizeIndexList(), 0, 0);
	}
	else
	{
		device->setTexture(this->vertex_shader, this->texture);
		device->setTexture(this->pixel_shader, this->texture);

		device->setVertexBufferTextured(this->vertexBufferTextured);
		device->setIndexBuffer(this->indexbuffer);

		device->drawIndexedTriangleList(this->indexbuffer->getSizeIndexList(), 0, 0);
	}
}

void Cylinder::update(float deltaTime)
{
}

void Cylinder::saveEditState() 
{
	PhysicsComponent* componentAttached = (PhysicsComponent*)this->findComponentbyType(AComponent::Physics, "Physics Component");
	if (componentAttached != nullptr)
	{
		AGameObject::saveEditState();
	}
}

void Cylinder::restoreEditState()
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

Cylinder::~Cylinder()
{
	this->constantbuffer->release();
	this->indexbuffer->release();
	this->vertexbuffer->release();
	AGameObject::~AGameObject();
}
