#pragma once
#include "AGameObject.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "Cube.h"
#include "TexturedCube.h"
#include "Plane.h"
#include "Capsule.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"

#include "OBJStructure.h"
#include "MeshManager.h"
#include "EditorAction.h"

#include <string>
#include <unordered_map>
#include <vector>

class EditorAction;

class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> ObjectList;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	enum PrimitiveType
	{
		CUBE,
		PLANE,
		SPHERE,
		CYLINDER,
		CAPSULE,
		TEXTURED_CUBE,
		PHYSICS_CUBE,
		PHYSICS_PLANE,
		BUNNY_OBJ
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(String name);
	AGameObject* getSelectedObject();
	ObjectList getAllObjects();

	int activeObjects();
	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);

	// Object instance
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	
	// Create/Delete/Select Object
	void createOBJMODEL(Mesh* mesh, String name, Texture* text);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(String name);
	void setSelectedObject(String name);
	void setSelectedObject(AGameObject* gameObject);

	// File System
	void saveEditStates();
	void restoreEditStates();
	void applyEditorAction(EditorAction* action);

	// Object generation
	//void hundredCube();
	void generatePhysicsCube();
	void generateBunnyObj();
	void generateArmadilloOBJ();
	void generateTeapotOBJ();
	void generateAllOBJ();

	// Render from file
	void createObjectFromFile(String name, AGameObject::PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale, bool rigidBody);
private:
	static GameObjectManager* sharedInstance;

	GameObjectManager();
	~GameObjectManager();

	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
private:
	AGameObject* SelectedObject;
	ObjectList GameObjectList;
	HashTable GameObjectTable;
// Object counter (heirarchy)
private:
	int cubeCounter = 0;
	int sphereCounter = 0;
	int cylinderCounter = 0;
	int planeCounter = 0;
	int TexturedCubecounter = 0;
	int PhysicsPlaneCounter = 0;
	int PhysicsCubeCounter = 0;
};