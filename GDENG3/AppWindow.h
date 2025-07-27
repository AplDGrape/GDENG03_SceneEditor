#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"

#include "Shaderlibrary.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "GameObjectManager.h"
#include "Cube.h"
#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Rectangle.h"

#include "Math.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <vector>

#include "EngineTime.h"

#include "InputListener.h"
#include "InputSystem.h"

#include "SceneCameraHandler.h"
#include "UIManager.h"
#include "TextureManager.h"
#include "MeshManager.h"

#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_dx11.h"
#include "IMGUI\imgui_impl_win32.h"

#include "BaseComponentSystem.h"
#include "EngineBackEnd.h"
#include "ActionHistory.h"
#include "Wireframe.h"

class Wireframe;
class AGameObject;

class AppWindow : public Window, public InputListener
{
public:
	//void update();

	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

	void onFocus() override;
	void onKillFocus() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& deltaMousePos) override;
	virtual void onLeftMouseDown(const Point& mousePosition) override;
	virtual void onLeftMouseUp(const Point& mousePosition) override;
	virtual void onRightMouseDown(const Point& mousePosition) override;
	virtual void onRightMouseUp(const Point& mousePosition) override;

	void initializeEngine();
	void createInterface();
public:
	static void initialize();
	static AppWindow* getInstance();
private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&){};
	AppWindow&operator=(AppWindow const&){};
public:
	Wireframe* getWireframe();
private:
	Wireframe* m_wireframe = nullptr;
private:
	static AppWindow* sharedInstance;
private:
	SwapChain* m_swap_chain;
	float ticks = 0.0f;
};
