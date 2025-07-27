#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
	this->localPosition = gameObject->getLocalPosition();
	this->localScale = gameObject->getLocalScale();
	this->localRotation = gameObject->getLocalRotation();
	this->localMatrix = gameObject->getLocalMatrix();
	this->objectName = gameObject->getName();
}

AGameObject::String EditorAction::getOwnerName()
{
	return this->objectName;
}

Vector3D EditorAction::getStoredPosition()
{
	return this->localPosition;
}

Vector3D EditorAction::getStoredScale()
{
	return this->localScale;
}

Vector3D EditorAction::getStoredRotation()
{
	return this->localRotation;
}

Matrix4x4 EditorAction::getStoredMatrix()
{
	return this->localMatrix;
}

EditorAction::~EditorAction()
{
}