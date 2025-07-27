#include "AppWindow.h"
#include "Debug.h"

//struct vec3
//{
//	float x, y, z;
//};
//
//struct vertex
//{
//	vec3 position;
//	vec3 color;
//};

//struct InstanceData
//{
//	Matrix4x4 transform;
//};
//
//__declspec(align(16))
//struct constant
//{
//	Matrix4x4 m_world;
//	Matrix4x4 m_view;
//	Matrix4x4 m_proj;
//	//unsigned int m_time;
//	float m_time = 0.0f;
//	float padding[3] = { 0.0f, 0.0f, 0.0f };
//};

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow::AppWindow()
{
}

//void AppWindow::update()
void AppWindow::onUpdate()
{
	Window::onUpdate();

	/*constant cc;
	cc.m_time = ::GetTickCount();*/

	this->ticks += EngineTime::getDeltaTime() * 1.0f;

	InputSystem::getInstance()->update();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.01, 0.01, 0.01, 0.01);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// Engine States
	// Holds the current state of the editor
	EngineBackEnd* backend = EngineBackEnd::getInstance();
	if (backend->getMode() == EngineBackEnd::EditorMode::PLAY) 
	{
		BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
		GameObjectManager::getInstance()->updateAll();
	}
	else if (backend->getMode() == EngineBackEnd::EditorMode::EDITOR) 
	{
		GameObjectManager::getInstance()->updateAll();
	}
	else if (backend->getMode() == EngineBackEnd::EditorMode::PAUSED) 
	{
		if (backend->insideFrameStep()) {
			BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
			GameObjectManager::getInstance()->updateAll();
			backend->endFrameStep();
		}
	}

	SceneCameraHandler::getInstance()->update();
	GameObjectManager::getInstance()->renderAll(rc.right - rc.left, rc.bottom - rc.top);

	UIManager::getInstance()->drawAllUI();

	m_wireframe->set(GraphicsEngine::getInstance()->getD3DDeviceContext());

	m_swap_chain->present(true);
}

// AppWindow singleton
void AppWindow::initialize()
{
	sharedInstance = new AppWindow();

	GraphicsEngine::initialize();

	sharedInstance->init();
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::initialize();

	m_wireframe = new Wireframe(GraphicsEngine::getInstance()->getD3Ddevice());

	BaseComponentSystem::initialize();
}

// Initialize all Engine Systems
void AppWindow::initializeEngine()
{
	//GraphicsEngine::initialize();
	EngineTime::initialize();
	EngineBackEnd::initialize();
	SceneCameraHandler::initialize();
	Shaderlibrary::initialize();
	TextureManager::initialize();
	MeshManager::initialize();
	ActionHistory::initialize();

	InputSystem::getInstance()->showCursor(true);

	GameObjectManager::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	m_swap_chain = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	// Def not hardcoded :) -> remind me to fix this
	Debug::Log("Initialize");
}

// Initialize UI
void AppWindow::createInterface()
{
	UIManager::initialize(this->m_hwnd);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	InputSystem::destroy();
	delete m_wireframe;
	m_swap_chain->release();
	GraphicsEngine::getInstance()->release();
	TextureManager::destroy();
	BaseComponentSystem::destroy();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'T' && m_wireframe != nullptr)
	{
		m_wireframe->toggle();
	}
	if (key == VK_ESCAPE)
	{
		// Safely close the window
		PostMessage(this->m_hwnd, WM_CLOSE, 0, 0);
	}
}

void AppWindow::onKeyUp(int key)
{
	
}

void AppWindow::onMouseMove(const Point& deltaMousePos)
{
	
}

void AppWindow::onLeftMouseDown(const Point& mousePosition)
{
	
}

void AppWindow::onLeftMouseUp(const Point& mousePosition)
{
	
}

void AppWindow::onRightMouseDown(const Point& mousePosition)
{
	
}

void AppWindow::onRightMouseUp(const Point& mousePosition)
{
	
}

Wireframe* AppWindow::getWireframe()
{
	return this->m_wireframe;
}

AppWindow* AppWindow::getInstance()
{
	if(sharedInstance != NULL)
	{
		return sharedInstance;
	}
}

AppWindow::~AppWindow()
{
}