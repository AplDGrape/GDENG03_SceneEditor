#include "Plane.h"
#include "AGameObject.h"

Plane::Plane(String name): Cube(name, PrimitiveType::PLANE)
{
	this->setTexturesVertexBuffer();
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.BASE_VERTEX_SHADER_NAME, &shaderdata.shaderByteCode, &shaderdata.sizeShader);

	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.01f, -0.5f),   Vector3D(1, 1, 1)},
		{Vector3D(-0.5f,  0.01f, -0.5f),   Vector3D(1, 1, 1)},
		{Vector3D( 0.5f,  0.01f, -0.5f),   Vector3D(1, 1, 1)},
		{Vector3D( 0.5f, -0.01f, -0.5f),   Vector3D(1, 1, 1)},

		//BACK FACE
		{Vector3D( 0.5f, -0.01f, 0.5f),    Vector3D(1, 1, 1)},
		{Vector3D( 0.5f,  0.01f, 0.5f),    Vector3D(1, 1, 1)},
		{Vector3D(-0.5f,  0.01f, 0.5f),    Vector3D(1, 1, 1)},
		{Vector3D(-0.5f, -0.01f, 0.5f),    Vector3D(1, 1, 1)}
	};

	this->vertex_buffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->vertex_buffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderdata.shaderByteCode, shaderdata.sizeShader);
	
	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	this->index_buffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->index_buffer->load(index_list, size_index_list);

	constant cc;
	cc.time = 0;

	this->constant_buffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constant_buffer->load(&cc, sizeof(constant));
}

void Plane::setTexturesVertexBuffer()
{
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.TEXTURED_VERTEX_SHADER_NAME, &shaderdataTexture.shaderByteCode, &shaderdataTexture.sizeShader);

	Vector3D position_list[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f, -0.1f, -0.5f)},
		{Vector3D(-0.5f,  0.1f, -0.5f)},
		{Vector3D( 0.5f,  0.1f, -0.5f)},
		{Vector3D( 0.5f, -0.1f, -0.5f)},

		//BACK FACE
		{Vector3D( 0.5f, -0.1f, 0.5f)},
		{Vector3D( 0.5f,  0.1f, 0.5f)},
		{Vector3D(-0.5f,  0.1f, 0.5f)},
		{Vector3D(-0.5f, -0.1f, 0.5f)}
	};

	Vector2D texcoord_list[] =
	{
		{Vector2D(0.0f, 0.0f)},
		{Vector2D(0.0f, 1.0f)},
		{Vector2D(1.0f, 0.0f)},
		{Vector2D(1.0f, 1.0f)}
	};

	Vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0], texcoord_list[1] },
		{ position_list[1], texcoord_list[0] },
		{ position_list[2], texcoord_list[2] },
		{ position_list[3], texcoord_list[3] },

		{ position_list[4], texcoord_list[1] },
		{ position_list[5], texcoord_list[0] },
		{ position_list[6], texcoord_list[2] },
		{ position_list[7], texcoord_list[3] },

		{ position_list[1], texcoord_list[1] },
		{ position_list[6], texcoord_list[0] },
		{ position_list[5], texcoord_list[2] },
		{ position_list[2], texcoord_list[3] },

		{ position_list[7], texcoord_list[1] },
		{ position_list[0], texcoord_list[0] },
		{ position_list[3], texcoord_list[2] },
		{ position_list[4], texcoord_list[3] },

		{ position_list[3], texcoord_list[1] },
		{ position_list[2], texcoord_list[0] },
		{ position_list[5], texcoord_list[2] },
		{ position_list[4], texcoord_list[3] },

		{ position_list[7], texcoord_list[1] },
		{ position_list[6], texcoord_list[0] },
		{ position_list[1], texcoord_list[2] },
		{ position_list[0], texcoord_list[3] }
	};

	this->vertexbufferTextured = GraphicsEngine::getInstance()->createTexturedVertexBuffer();
	this->vertexbufferTextured->load(vertex_list, sizeof(Vertex), ARRAYSIZE(vertex_list), shaderdataTexture.shaderByteCode, shaderdataTexture.sizeShader);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};


	this->indexbufferTextured = GraphicsEngine::getInstance()->createIndexBuffer();
	this->indexbufferTextured->load(index_list, ARRAYSIZE(index_list));

	constant cc;
	cc.time = 0;
	this->constant_buffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constant_buffer->load(&cc, sizeof(constant));
}

void Plane::draw(int width, int height)
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

	this->ComputeLocalMatrix();
	cc.world = this->getLocalMatrix();

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.view = cameraMatrix;

	/*
	cc.projection.setOrthoLH
	(
		width / 300.0f,
		height / 300.0f,
		-4.0f,
		4.0f
	);
	*/
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
		device->setIndexBuffer(this->indexbufferTextured);

		device->drawIndexedTriangleList(this->indexbufferTextured->getSizeIndexList(), 0, 0);
	}
	
}

Plane::~Plane()
{
	this->constant_buffer->release();
	this->index_buffer->release();
	this->vertex_buffer->release();
}