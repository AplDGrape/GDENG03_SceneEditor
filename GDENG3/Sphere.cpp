#include "Sphere.h"
#include "PhysicsComponent.h"

Sphere::Sphere(String name):AGameObject(name, PrimitiveType::SPHERE)
{
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.BASE_VERTEX_SHADER_NAME, &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.TEXTURED_VERTEX_SHADER_NAME, &shaderdataTexture.shaderByteCode, &shaderdataTexture.sizeShader);

	float radius = 1.0f;
	int stackCount = 34;
	int sectorCount = 34;

	float x, y, z, xy;
	float pi = 3.1415926;
	float sectorStep = 2 * pi / (float)sectorCount;
	float stackStep = pi / (float)stackCount;
	float sectorAngle, stackAngle;
	float s, t;

	for(int i = 0; i <= stackCount; i++)
	{
		stackAngle = pi / 2.0f - i * stackStep;
		xy = radius * cosf(stackAngle);
		y = radius * sinf(stackAngle);

		for(int j = 0; j <= sectorCount; j++)
		{
			sectorAngle = j * sectorStep;
			z = xy * cosf(sectorAngle);
			x = xy * sinf(sectorAngle);

			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			
			vertex vertexsector = { Vector3D(x, y, z), Vector3D(1,1,1),  Vector3D(1,1,1) };
			Vertex vertexsectorTextured = { Vector3D(x, y, z), Vector2D(s, t) };
			this->vertices.push_back(vertexsector);
			this->verticesTextured.push_back(vertexsectorTextured);
		}
	}



	this->verterbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->verterbuffer->load(&(this->vertices[0]), sizeof(vertex), this->vertices.size(), shaderdata.shaderByteCode, shaderdata.sizeShader);

	this->verterBufferTextured = GraphicsEngine::getInstance()->createTexturedVertexBuffer();
	this->verterBufferTextured->load(&(this->verticesTextured[0]), sizeof(Vertex), this->verticesTextured.size(), shaderdataTexture.shaderByteCode, shaderdataTexture.sizeShader);

	int k1, k2;

	for(int i = 0; i < stackCount; i++)
	{
		k1 = i * (sectorCount + 1);
		k2 = k1 + sectorCount + 1;

		for(int j = 0; j < sectorCount; j++)
		{
			if (i != 0)
			{
				this->indices.push_back(k1);
				this->indices.push_back(k1 + 1);
				this->indices.push_back(k2);
			}

			if (i != (stackCount - 1))
			{
				this->indices.push_back(k1 + 1);
				this->indices.push_back(k2 + 1);
				this->indices.push_back(k2);
			}

			k1++;
			k2++;
		}
	}

	this->indexbuffer = GraphicsEngine::getInstance()->createIndexBuffer();

	this->indexbuffer->load(&(this->indices[0]), this->indices.size());
	constant cc;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));
}

void Sphere::draw(int width, int height)
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
		device->setVertexBuffer(this->verterbuffer);
		device->setIndexBuffer(this->indexbuffer);

		device->drawIndexedTriangleList(this->indexbuffer->getSizeIndexList(), 0, 0);
	}
	else
	{
		device->setTexture(this->vertex_shader, this->texture);
		device->setTexture(this->pixel_shader, this->texture);

		device->setVertexBufferTextured(this->verterBufferTextured);
		device->setIndexBuffer(this->indexbuffer);

		device->drawIndexedTriangleList(this->indexbuffer->getSizeIndexList(), 0, 0);
	}
}

void Sphere::update(float deltaTime)
{
}

void Sphere::saveEditState(){
	PhysicsComponent* componentAttached = (PhysicsComponent*)this->findComponentbyType(AComponent::Physics, "Physics Component");
	if (componentAttached != nullptr)
	{
		AGameObject::saveEditState();
	}
}

void Sphere::restoreEditState()
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

Sphere::~Sphere()
{
	this->constantbuffer->release();
	this->indexbuffer->release();
	this->verterbuffer->release();
	AGameObject::~AGameObject();
}