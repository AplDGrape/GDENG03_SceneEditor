#include "TexturedCube.h"

TexturedCube::TexturedCube(String name): Cube(name, TEXTURED_CUBE)
{
	// Load texture from file
	Shaderlibrary::getInstance()->requestVertexShaderData(namesShader.TEXTURED_VERTEX_SHADER_NAME, &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	Texture* tex = TextureManager::getInstance()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");

	this->setObjectTexture(tex);
	this->setTextureFlag();

	Vector3D position_list[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f)},
		{Vector3D(-0.5f,  0.5f, -0.5f)},
		{Vector3D( 0.5f,  0.5f, -0.5f)},
		{Vector3D( 0.5f, -0.5f, -0.5f)},

		//BACK FACE
		{Vector3D( 0.5f, -0.5f, 0.5f)},
		{Vector3D( 0.5f,  0.5f, 0.5f)},
		{Vector3D(-0.5f,  0.5f, 0.5f)},
		{Vector3D(-0.5f, -0.5f, 0.5f)}
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
	this->vertexbufferTextured->load(vertex_list, sizeof(Vertex), ARRAYSIZE(vertex_list), shaderdata.shaderByteCode, shaderdata.sizeShader);

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

	// Index Buffer
	this->index_Buffer = GraphicsEngine::getInstance()->createIndexBuffer();
	this->index_Buffer->load(index_list, ARRAYSIZE(index_list));
	
	//constant cc = {};
	constant cc;
	cc.time = 0;
	this->constant_Buffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constant_Buffer->load(&cc, sizeof(constant));
}

void TexturedCube::draw(int width, int height)
{
	if(this->getObjectTexture() != NULL)
	{
		this->vertex_shader = Shaderlibrary::getInstance()->getVertexShader(namesShader.TEXTURED_VERTEX_SHADER_NAME);
		this->pixel_shader = Shaderlibrary::getInstance()->getPixelShader(namesShader.TEXTURED_PIXEL_SHADER_NAME);

		DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();

		constant cc;
		this->ComputeLocalMatrix();

		cc.world = this->getLocalMatrix();

		Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
		cc.view = cameraMatrix;

		float aspectRatio = (float)width / (float)height;

		cc.projection.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

		DeviceContext* device = GraphicsEngine::getInstance()->getImmediateDeviceContext();

		this->constant_Buffer->update(device, &cc);

		device->setConstantBuffer(this->vertex_shader, this->constant_Buffer);
		device->setConstantBuffer(this->pixel_shader, this->constant_Buffer);

		device->setVertexShader(this->vertex_shader);
		device->setPixelShader(this->pixel_shader);

		// Set vertex shader and pixel shader for the object
		device->setTexture(this->vertex_shader, this->texture);
		device->setTexture(this->pixel_shader, this->texture);

		device->setVertexBufferTextured(this->vertexbufferTextured);
		device->setIndexBuffer(this->index_Buffer);

		device->drawIndexedTriangleList(this->index_Buffer->getSizeIndexList(), 0, 0);
	}
	else
	{
		Cube::draw(width, height);
	}
}

void TexturedCube::update(float deltaTime)
{
}

TexturedCube::~TexturedCube()
{
}