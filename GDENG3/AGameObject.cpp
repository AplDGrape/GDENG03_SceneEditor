#include "AGameObject.h"
#include "EditorAction.h"

AGameObject::AGameObject(String name, PrimitiveType type)
{
	this->objectType = type;
	this->name = name;
	this->Position = Vector3D::zeros();
	this->Rotation = Vector3D::zeros();
	this->Scale = Vector3D::ones();
	this->LocalMatrix.setIdentity();
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->Position = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setPosition(Vector3D pos)
{
	this->Position = pos;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->Position;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->Scale = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setScale(Vector3D scale)
{
	this->Scale = scale;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalScale()
{
	return this->Scale;
}

void AGameObject::setLocalMatrix(float matrix[16])
{
	float Matrix[4][4];

	Matrix[0][0] = matrix[0];
	Matrix[0][1] = matrix[1];
	Matrix[0][2] = matrix[2];
	Matrix[0][3] = matrix[3];

	Matrix[1][0] = matrix[4];
	Matrix[1][1] = matrix[5];
	Matrix[1][2] = matrix[6];
	Matrix[1][3] = matrix[7];

	Matrix[2][0] = matrix[8];
	Matrix[2][1] = matrix[9];
	Matrix[2][2] = matrix[10];
	Matrix[2][3] = matrix[11];

	Matrix[3][0] = matrix[12];
	Matrix[3][1] = matrix[13];
	Matrix[3][2] = matrix[14];
	Matrix[3][3] = matrix[15];

	Matrix4x4 coordinate;
	coordinate.setIdentity();
	coordinate.setMatrix(Matrix);

	Matrix4x4 scale;
	scale.setIdentity();
	scale.setScale(this->Scale);

	Matrix4x4 translate;
	translate.setIdentity();
	translate.setTranslation(this->Position);

	this->LocalMatrix = scale.multiplyTo(translate.multiplyTo(coordinate));
	this->overrideMatrix = true;
}

Matrix4x4 AGameObject::getLocalMatrix()
{
	return this->LocalMatrix;
}

void AGameObject::setRotation(float x, float y, float z)
{
	//this->Rotation = Vector3D(x, y, z);
	this->orientation = {};
	this->orientation.x = x;
	this->orientation.y = y;
	this->orientation.z = z;
	this->overrideMatrix = false;
}

void AGameObject::setRotation(Vector3D rot)
{
	//this->Rotation = rot;
	this->orientation = {};
	this->orientation.x = rot.m_x;
	this->orientation.y = rot.m_y;
	this->orientation.z = rot.m_z;
	this->overrideMatrix = false;
}

void AGameObject::setRotationX(float x)
{
	this->orientation = {};
	this->orientation.x = x;
	this->overrideMatrix = false;
}

void AGameObject::setRotationY(float y)
{
	this->orientation = {};
	this->orientation.y = y;
	this->overrideMatrix = false;
}

void AGameObject::setRotationz(float z)
{
	this->orientation = {};
	this->orientation.z = z;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalRotation()
{
	return Vector3D(this->orientation.x, this->orientation.y, this->orientation.z);
}

void AGameObject::enable()
{
	this->enabled = true;
}

void AGameObject::disable()
{
	this->enabled = false;
}

bool AGameObject::getStatus()
{
	return this->enabled;
}

AGameObject::String AGameObject::getName()
{
	//return string();
	return this->name;
}

void AGameObject::setName(String name)
{
	this->name = name;
}

AGameObject::PrimitiveType AGameObject::getType()
{
	return this->objectType;
}

void AGameObject::ComputeLocalMatrix()
{
	this->Summation.setIdentity();
	this->translate.setIdentity();
	this->ScaleMatrix.setIdentity();

	translate.setTranslation(this->getLocalPosition());
	ScaleMatrix.setScale(this->getLocalScale());
	rotation = Vector3D(this->getLocalRotation());

	this->RotationZ.setIdentity();
	this->RotationZ.setRotationZ(rotation.m_z);

	this->RotationF.setIdentity();
	this->RotationF.setRotationX(rotation.m_x);

	this->RotationGl.setIdentity();
	this->RotationGl.setRotationY(rotation.m_y);

	this->RotationTotal.setIdentity();
	this->RotationTotal = this->RotationTotal.multiplyTo(RotationF.multiplyTo(RotationGl.multiplyTo(RotationZ)));
	this->Summation = this->Summation.multiplyTo(ScaleMatrix.multiplyTo(this->RotationTotal));
	this->Summation = this->Summation.multiplyTo(this->translate);
	this->LocalMatrix = this->Summation;
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 MatrixAll;
	MatrixAll.setIdentity();

	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->Position);

	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(Vector3D::ones());

	Vector3D rotation = this->getLocalRotation();

	Matrix4x4 xMatrix;
	xMatrix.setIdentity();
	xMatrix.setRotationX(rotation.m_x);

	Matrix4x4 yMatrix;
	yMatrix.setIdentity();
	yMatrix.setRotationY(rotation.m_y);

	Matrix4x4 zMatrix;
	zMatrix.setIdentity();
	zMatrix.setRotationY(rotation.m_z);

	Matrix4x4 rotationMatrix;
	rotationMatrix.setIdentity();
	rotationMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	MatrixAll = MatrixAll.multiplyTo(scaleMatrix.multiplyTo(rotationMatrix));
	MatrixAll = MatrixAll.multiplyTo(translationMatrix);

	return *MatrixAll.m_mat;
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i] == component) {
			index = i;
			this->componentList.erase(this->componentList.begin() + index);
			break;
		}
	}
}

AComponent* AGameObject::findComponentByName(String name)
{
	AComponent* found = nullptr;
	for(int i = 0; i < this->componentList.size(); i++)
	{
		if(this->componentList[i]->getName() == name)
		{
			found = this->componentList[i];
		}
	}
	return found;
}

AComponent* AGameObject::findComponentbyType(AComponent::ComponentType type, String name)
{
	AComponent* found = nullptr;
	for (int i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type)
		{
			found = this->componentList[i];
			
		}
	}
	return found;
}

AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList foundList;

	for (int i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

void AGameObject::setObjectTexture(Texture* texture)
{
	this->texture = texture;
}

Texture* AGameObject::getObjectTexture()
{
	return this->texture;
}

void AGameObject::setTextureFlag()
{
	this->isTextured = true;
}

bool AGameObject::textureFlag()
{
	return this->isTextured;
}

void AGameObject::saveEditState()
{
	if (this->lastEditState == NULL) 
	{
		this->lastEditState = new EditorAction(this);
	}
}

void AGameObject::restoreEditState()
{
	if (this->lastEditState != NULL) 
	{
		this->Position = this->lastEditState->getStoredPosition();
		this->Scale = this->lastEditState->getStoredScale();
		this->Rotation = this->lastEditState->getStoredRotation();

		this->LocalMatrix = this->lastEditState->getStoredMatrix();

		this->lastEditState = NULL;
	}
}

void AGameObject::awake()
{
}

AGameObject::~AGameObject()
{
	this->vertex_shader->release();
	this->pixel_shader->release();
}
