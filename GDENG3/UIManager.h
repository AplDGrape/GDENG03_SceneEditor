#pragma once
#include "AUIScreen.h"
#include "UINames.h"
#include "GraphicsEngine.h"
#include "ProfilerScreen.h"
#include "MenuScreen.h"
#include "InspectorScreen.h"
#include "HierarchyScreen.h"
#include "CreditsScreen.h"
#include "ColourPickerScreen.h"
#include "DemoScreen.h"
#include "ScreenPlayBack.h"
#include "ScreenActions.h"
#include "DebugConsoleScreen.h"

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();
	void hideCreditsScreen();
	void showCreditsScreen();

	void hideColorPickerScreen();
	void showColorPickerScreen();

	void showDemoScreen();
	void hideDemoScreen();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;
	//static const int WINDOW_WIDTH = 1024;
	//static const int WINDOW_HEIGHT = 768;
private:
	UIManager(HWND windowHandle);
	~UIManager();

	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&){};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
private:
	bool showDemo = false;
	bool showCredits = false;
	bool showColourPicker = false;
public:
	static ImVec4 logoTint;
};