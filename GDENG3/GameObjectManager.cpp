#include "GameObjectManager.h"
#include "EngineTime.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager::GameObjectManager()
{
	this->SelectedObject = NULL;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::destroy()
{
	delete sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(String name)
{
	return this->GameObjectTable.at(name);
}

GameObjectManager::ObjectList GameObjectManager::getAllObjects()
{
	return this->GameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->GameObjectList.size();
}

void GameObjectManager::updateAll()
{
	for(AGameObject* gameobject: this->GameObjectList)
	{
		for(AComponent* component: gameobject->getComponentsOfType(AComponent::Physics))
		{
			component->perform(EngineTime::getDeltaTime());
		}
	}
	/*
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->update(EngineTime::getDeltaTime());
	}
	*/
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight)
{
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		if (this->GameObjectList[i]->getStatus() == true)
			this->GameObjectList[i]->draw(viewportWidth, viewportHeight);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	if (this->GameObjectTable[gameObject->getName()] != NULL) {
		int gameObjectcount = 1;
		String revisedString = gameObject->getName() + "(" + std::to_string(gameObjectcount) + ")";
		for(int i = 0; i < this->GameObjectList.size(); i++)
		{
			if(this->GameObjectTable[revisedString] != NULL)
			{
				gameObjectcount++;
				revisedString = gameObject->getName() + "(" + std::to_string(gameObjectcount) + ")";
			}
			else
			{
				break;
			}
		}
		gameObject->setName(revisedString);
		this->GameObjectTable[revisedString] = gameObject;
	}
	else {
		this->GameObjectTable[gameObject->getName()] = gameObject;
	}
	
	this->GameObjectList.push_back(gameObject);
}

// Create Objects
void GameObjectManager::createObject(PrimitiveType type)
{
	if(type == PrimitiveType::CUBE)
	{
		Cube* cube = new Cube("Cube", AGameObject::CUBE);
		cube->setPosition(0.0f, 1.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
		
	}
	else if (type == PrimitiveType::PLANE)
	{
		Plane* plane = new Plane("Plane");
		plane->setPosition(0.0f, 1.0f, 0.0f);
		plane->setScale(10.0f, 1.0f, 10.0f);
		this->addObject(plane);
		
	}
	else if (type == PrimitiveType::CYLINDER)
	{
		Cylinder* cylinder = new Cylinder("Cylinder");
		cylinder->setPosition(0.0f, 1.0f, 0.0f);
		cylinder->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cylinder);
		
	}
	else if (type == PrimitiveType::SPHERE)
	{
		Sphere* sphere = new Sphere("Sphere");
		sphere->setPosition(0.0f, 1.0f, 0.0f);
		sphere->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(sphere);
	
	}
	else if(type == PrimitiveType::CAPSULE)
	{
		Capsule* capsule = new Capsule("Capsule");
		capsule->setPosition(0.0f, 1.0f, 0.0f);
		capsule->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(capsule);
	}
	else if(type == PrimitiveType::TEXTURED_CUBE)
	{
		TexturedCube* Texcube = new TexturedCube("Textured Cube");
		Texcube->setPosition(0.0f, 1.0f, 0.0f);
		Texcube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(Texcube);
	}
	else if(type == PrimitiveType::CAPSULE)
	{
		Capsule* capsule = new Capsule("Capsule");
		capsule->setPosition(0.0f, 1.0f, 0.0f);
		capsule->setScale(0.25f, 0.25f, 0.25f);
		this->addObject(capsule);
	}
	else if(type == PrimitiveType::PHYSICS_CUBE)
	{
		PhysicsCube* physicsCube = new PhysicsCube("Physics Cube");
		this->addObject(physicsCube);
	}
	else if(type == PrimitiveType::PHYSICS_PLANE)
	{
		PhysicsPlane* physicsplane = new PhysicsPlane("Physics Plane");
		this->addObject(physicsplane);
	}
}

void GameObjectManager::generatePhysicsCube()
{
	for(int i = 0; i < 20; i++)
	{
		PhysicsCube* physicsCube = new PhysicsCube("Physics Cube");
		this->addObject(physicsCube);
	}
}

// Create OBJ instance
void GameObjectManager::createOBJMODEL(Mesh* mesh, String name, Texture* text)
{
	OBJStructure* obj = new OBJStructure(mesh, text, name);

	obj->setPosition(0.0f, 1.0f, 0.0f);
	obj->setScale(2.0f, 2.0f, 2.0f);
	this->addObject(obj);
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->GameObjectTable.erase(gameObject->getName());
	int index = -1;

	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		if(this->GameObjectList[i]->getName() == gameObject->getName())
		{
			index = i;
			this->GameObjectList.erase(this->GameObjectList.begin() + index);
			break;
		}
	}
}

void GameObjectManager::deleteObjectByName(String name)
{
	this->deleteObject(this->GameObjectTable.at(name));
}

void GameObjectManager::setSelectedObject(String name)
{
	this->setSelectedObject(this->GameObjectTable.at(name));
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	this->SelectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return this->SelectedObject;
}

void GameObjectManager::saveEditStates()
{
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->saveEditState();
	}
}

void GameObjectManager::restoreEditStates()
{
	for (int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->restoreEditState();
	}
}

void GameObjectManager::applyEditorAction(EditorAction* action)
{
	AGameObject* object = this->findObjectByName(action->getOwnerName());

	if (object != NULL) {
		
		object->setLocalMatrix(*action->getStoredMatrix().m_mat);
		object->setPosition(action->getStoredPosition());
		object->setRotation(action->getStoredRotation().m_x, action->getStoredRotation().m_y, action->getStoredRotation().m_z);
		object->setScale(action->getStoredScale());
	}
}

//void GameObjectManager::hundredCubes()
//{
//	int max = 1.5f;
//	int min = -2.5f;
//	Math math;
//
//	for (int i = 0; i < 100; i++)
//	{
//		float x = math.getRandom(min, max);
//		float y = math.getRandom(min, max);
//		Cube* cube = new Cube("Cube", AGameObject::CUBE);
//		cube->setPosition(x, y, 0.0f);
//		cube->setScale(1.0f, 1.0f, 1.0f);
//		this->addObject(cube);
//	}
//}

void GameObjectManager::generateTeapotOBJ()
{
	// Load mesh
	std::wstring teapotPath = L"Assets/Meshes/OBJ/teapot.obj";
	Mesh* teapotMesh = MeshManager::getInstance()->createMeshFromFile(teapotPath.c_str());

	if (!teapotMesh) {
		OutputDebugStringA("Failed to load teapot.obj\n");
	}
	else {
		
		Texture* teapotTex = TextureManager::getInstance()->createTextureFromFile(L"Assets/Textures/brick.png");
		//Texture* bunnyTex = nullptr;
		GameObjectManager::getInstance()->createOBJMODEL(teapotMesh, "Utah Teapot", teapotTex);

		AGameObject* obj = findObjectByName("Utah Teapot");
		if (obj) {
			obj->setScale(Vector3D(5.0f, 5.0f, 5.0f));
		}
	}
}

void GameObjectManager::generateBunnyObj()
{
	// Load mesh
	std::wstring bunnyPath = L"Assets/Meshes/OBJ/bunny.obj";
	Mesh* bunnyMesh = MeshManager::getInstance()->createMeshFromFile(bunnyPath.c_str());

	if (!bunnyMesh) {
		OutputDebugStringA("Failed to load bunny.obj\n");
	}
	else {
		Texture* bunnyTex = TextureManager::getInstance()->createTextureFromFile(L"Assets/Textures/brick.png");
		//Texture* bunnyTex = nullptr;
		GameObjectManager::getInstance()->createOBJMODEL(bunnyMesh, "Stanford Bunny", bunnyTex);

		AGameObject* obj = findObjectByName("Stanford Bunny");
		if (obj) {
			obj->setScale(Vector3D(20.0f, 20.0f, 20.0f));
		}
	}
}

void GameObjectManager::generateArmadilloOBJ()
{
	// Load mesh
	std::wstring armadilloPath = L"C:Assets/Meshes/OBJ/armadillo.obj";
	Mesh* armadilloMesh = MeshManager::getInstance()->createMeshFromFile(armadilloPath.c_str());

	if (!armadilloMesh) {
		OutputDebugStringA("Failed to load armadillo.obj\n");
	}
	else {
		Texture* armdailloTex = TextureManager::getInstance()->createTextureFromFile(L"Assets/Textures/brick.png");
		//Texture* armdailloTex = nullptr;
		GameObjectManager::getInstance()->createOBJMODEL(armadilloMesh, "Armadillo", armdailloTex);
	}
}

void GameObjectManager::generateAllOBJ()
{
	// Load teapot mesh
	std::wstring teapotPath = L"Assets/Meshes/OBJ/teapot.obj";
	Mesh* teapotMesh = MeshManager::getInstance()->createMeshFromFile(teapotPath.c_str());

	if (!teapotMesh) {
		OutputDebugStringA("Failed to load teapot.obj\n");
	}
	else {

		Texture* teapotTex = TextureManager::getInstance()->createTextureFromFile(L"Assets/Textures/brick.png");
		//Texture* bunnyTex = nullptr;
		GameObjectManager::getInstance()->createOBJMODEL(teapotMesh, "OBJ 1", teapotTex);

		AGameObject* obj = findObjectByName("OBJ 1");
		if (obj) {
			obj->setPosition(Vector3D(-10.0f, 0.0f, 0.0f));
			obj->setScale(Vector3D(5.0f, 5.0f, 5.0f));
		}
	}

	// Load bunny mesh
	std::wstring bunnyPath = L"Assets/Meshes/OBJ/bunny.obj";
	Mesh* bunnyMesh = MeshManager::getInstance()->createMeshFromFile(bunnyPath.c_str());

	if (!bunnyMesh) {
		OutputDebugStringA("Failed to load bunny.obj\n");
	}
	else {
		Texture* bunnyTex = TextureManager::getInstance()->createTextureFromFile(L"Assets/Textures/brick.png");
		//Texture* bunnyTex = nullptr;
		GameObjectManager::getInstance()->createOBJMODEL(bunnyMesh, "OBJ 2", bunnyTex);

		AGameObject* obj = findObjectByName("OBJ 2");
		if (obj) {
			obj->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
			obj->setScale(Vector3D(20.0f, 20.0f, 20.0f));
		}
	}

	// Load armadillo mesh
	std::wstring armadilloPath = L"C:Assets/Meshes/OBJ/armadillo.obj";
	Mesh* armadilloMesh = MeshManager::getInstance()->createMeshFromFile(armadilloPath.c_str());

	if (!armadilloMesh) {
		OutputDebugStringA("Failed to load armadillo.obj\n");
	}
	else {
		Texture* armdailloTex = TextureManager::getInstance()->createTextureFromFile(L"Assets/Textures/brick.png");
		//Texture* armdailloTex = nullptr;
		GameObjectManager::getInstance()->createOBJMODEL(armadilloMesh, "OBJ 3", armdailloTex);

		AGameObject* obj = findObjectByName("OBJ 3");
		if (obj) {
			obj->setPosition(Vector3D(10.0f, 0.0f, 0.0f));
		}
	}
}

// Render from File
void GameObjectManager::createObjectFromFile(String name, AGameObject::PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale, bool rigidBody)
{
	if(rotation.m_y == 90.0f)
	{
		rotation.m_y = 99.0f;
	}

	if (type == AGameObject::PrimitiveType::CUBE) 
	{
		Cube* cube = new Cube(name, AGameObject::CUBE);

		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);

		if(rigidBody)
		{
			cube->ComputeLocalMatrix();
			cube->attachComponent(new PhysicsComponent("Physics Component", cube));
			
		}

		this->addObject(cube);
	}
	else if (type == AGameObject::PrimitiveType::PLANE)
	{
		Plane* plane = new Plane(name);

		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);

		if (rigidBody)
		{
			plane->ComputeLocalMatrix();
			plane->attachComponent(new PhysicsComponent("Physics Component", plane));
			PhysicsComponent* component = (PhysicsComponent*)plane->findComponentbyType(AComponent::ComponentType::Physics, "Physics Component");
			component->getRigidBody()->setType(BodyType::KINEMATIC);
		}

		this->addObject(plane);
	}
	else if(type == AGameObject::PrimitiveType::CAPSULE)
	{
		Capsule* capsule = new Capsule("Capsule");

		capsule->setPosition(position);
		capsule->setRotation(rotation);
		capsule->setScale(scale);

		if (rigidBody)
		{
			capsule->ComputeLocalMatrix();
			capsule->attachComponent(new PhysicsComponent("Physics Component", capsule));
		}

		this->addObject(capsule);
	}
	else if (type == AGameObject::PrimitiveType::TEXTURED_CUBE) 
	{
		TexturedCube* texturedcube = new TexturedCube(name);

		texturedcube->setPosition(position);
		texturedcube->setRotation(rotation);
		texturedcube->setScale(scale);

		this->addObject(texturedcube);
	}
	else if (type == AGameObject::PrimitiveType::PHYSICS_CUBE) 
	{
		PhysicsCube* physicscube = new PhysicsCube(name);

		physicscube->setPosition(position);
		physicscube->setRotation(rotation);
		physicscube->setScale(scale);

		this->addObject(physicscube);
	}
	else if (type == AGameObject::PrimitiveType::PHYSICS_PLANE) 
	{
		PhysicsPlane* plane = new PhysicsPlane(name);

		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);

		this->addObject(plane);
	}
	else if(type == AGameObject::PrimitiveType::CYLINDER)
	{
		Cylinder* cylinder = new Cylinder(name);

		cylinder->setPosition(position);
		cylinder->setRotation(rotation);
		cylinder->setScale(scale);

		if (rigidBody)
		{
			cylinder->ComputeLocalMatrix();
			cylinder->attachComponent(new PhysicsComponent("Physics Component", cylinder));
		}

		this->addObject(cylinder);
	}
	else if(type == AGameObject::PrimitiveType::SPHERE)
	{
		Sphere* sphere = new Sphere(name);

		sphere->setPosition(position);
		sphere->setRotation(rotation);
		sphere->setScale(scale);

		if (rigidBody)
		{
			sphere->ComputeLocalMatrix();
			sphere->attachComponent(new PhysicsComponent("Physics Component", sphere));
			PhysicsComponent* component = (PhysicsComponent*)sphere->findComponentbyType(AComponent::ComponentType::Physics, "Physics Component");

		}

		this->addObject(sphere);
	}
}

GameObjectManager::~GameObjectManager()
{
	delete this->SelectedObject;
}