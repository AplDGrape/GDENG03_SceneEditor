#include "Camera.h"
#include <iostream>

Camera::Camera(String name) :AGameObject(name, AGameObject::CAMERA)
{
	// Set Default Position
	this->setPosition(0.0f, 2.0f, -2.0f);
	//this->cameraFront = Vector3D(0.0f, 0.0f, -1.0f);
	//this->cameraUp = Vector3D(0.0f, 1.0f, 0.0f);

	Vector3D direction = Vector3D(0.0f, 2.0f, -30.0f) - this->getLocalPosition();
	direction = Vector3D::normalize(direction);

	pitch = std::asin(direction.m_y);
	yaw = std::atan2(direction.m_x, -direction.m_z);

	InputSystem::getInstance()->addListener(this);
	this->updateViewMatrix();
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();

	Matrix4x4 temp;

	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));
	
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale)+1.0f)/2.0f));

	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));

	//cc.m_world *= temp;
	
	// Apply pitch (X) and yaw (Y) rotation
	temp.setIdentity();
	temp.setRotationX(pitch);
	worldCam = worldCam.multiplyTo(temp);

	temp.setIdentity();
	temp.setRotationY(yaw);
	worldCam = worldCam.multiplyTo(temp);

	// Apply position
	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.multiplyTo(temp);

	/*m_world_cam = world_cam;

	world_cam.getInverse();*/

	// Invert to get view matrix
	worldCam.getInverse();
	this->LocalMatrix = worldCam;

	//m_cameraViewMatrix = m_camera.getViewMatrix();
	//m_cameraProjMatrix = m_camera.getProjectionMatrix();
}

void Camera::defaultmode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) 
	{
		z += rate;
	
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) 
	{
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) 
	{
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) 
	{
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::AerialMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) 
	{
		y += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S'))
	{
		y -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) 
	{
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) 
	{
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::DownWardMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) 
	{
		y -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) 
	{
		y += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) 
	{
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D'))
	{
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::RightViewMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) 
	{
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S'))
	{
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) 
	{
		z += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) 
	{
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::LeftViewMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) 
	{
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) 
	{
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) 
	{
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) 
	{
		z += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::update(float deltaTime)
{
	float speed = 5.0f * deltaTime;

	// Get orientation-based vectors
	Matrix4x4 rot;
	rot.setIdentity();

	Matrix4x4 temp;
	temp.setIdentity();
	temp.setRotationX(pitch);
	rot = rot.multiplyTo(temp);

	temp.setIdentity();
	temp.setRotationY(yaw);
	rot = rot.multiplyTo(temp);

	Vector3D forward = rot.getZDirection() * -1.0f; // Forward is -Z
	Vector3D right = rot.getXDirection();           // Right is +X
	Vector3D up = Vector3D(0, 1, 0);                // World up

	Vector3D pos = this->getLocalPosition();

	// Movement
	if (InputSystem::getInstance()->isKeyDown('W')) pos = pos - forward * speed;
	if (InputSystem::getInstance()->isKeyDown('S')) pos = pos + forward * speed;
	if (InputSystem::getInstance()->isKeyDown('A')) pos = pos - right * speed;
	if (InputSystem::getInstance()->isKeyDown('D')) pos = pos + right * speed;
	if (InputSystem::getInstance()->isKeyDown(VK_SPACE)) pos = pos + up * speed;
	if (InputSystem::getInstance()->isKeyDown(VK_CONTROL)) pos = pos - up * speed;

	this->setPosition(pos);
	this->updateViewMatrix();
}

void Camera::draw(int width, int height)
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->LocalMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point& deltaMousePos)
{
	if (RightMouseDown)
	{
		float sensitivity = 0.002f;
		yaw += deltaMousePos.m_x * sensitivity;
		pitch += deltaMousePos.m_y * sensitivity;

		// Clamp pitch to avoid flipping
		if (pitch > 1.5f) pitch = 1.5f;
		if (pitch < -1.5f) pitch = -1.5f;
	}
}

void Camera::onLeftMouseDown(const Point& mousePosition)
{
}

void Camera::onLeftMouseUp(const Point& mousePosition)
{
}

void Camera::onRightMouseDown(const Point& mousePosition)
{
	this->RightMouseDown = true;
}

void Camera::onRightMouseUp(const Point& mousePosition)
{
	this->RightMouseDown = false;
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}