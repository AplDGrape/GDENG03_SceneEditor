#include "OBJStructure.h"

OBJStructure::OBJStructure(Mesh* mesh, Texture* texture, String name): AGameObject(name, PrimitiveType::OBJ)
{
	this->meshModel = mesh;
	this->setObjectTexture(texture);

	this->setTextureFlag();

	constant cc;
	cc.time = 0;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));

	this->vertex_shader = Shaderlibrary::getInstance()->getVertexShader(namesShader.TEXTURED_VERTEX_SHADER_NAME);
	this->pixel_shader = Shaderlibrary::getInstance()->getPixelShader(namesShader.MESHLAYOUT_PIXEL_SHADER_NAME);
}

void OBJStructure::draw(int width, int height)
{
	ShaderNames shaderNames;

	DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();

	constant cc;
	this->ComputeLocalMatrix();
	cc.world = this->getLocalMatrix();

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

	device->setTexture(this->vertex_shader, this->texture);
	device->setTexture(this->pixel_shader, this->texture);

	device->setVertexBufferTextured(this->meshModel->getVertexBuffer());
	device->setIndexBuffer(this->meshModel->getIndexBuffer());

	device->drawIndexedTriangleList(this->meshModel->getIndexBuffer()->getSizeIndexList(), 0, 0);

	this->oldDelta = this->newDelta;
	this->newDelta += this->ticks;

	this->deltaTime = (oldDelta) ? ((newDelta - oldDelta) / 1000.0f) : 0;
}

void OBJStructure::update(float deltaTime)
{
}

OBJStructure::~OBJStructure()
{
}