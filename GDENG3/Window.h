#pragma once
#pragma comment(lib,"d3d11.lib")
#define NOMINMAX // To avoid conflict with Windows.h MIN and MAX declarations

#include <Windows.h>
#include "EngineTime.h"

class Window
{
public:
	Window();

	//Initialize the window
	bool init();
	bool broadcast();

	//Release the window
	bool release();
	bool isRun();

	HWND gethwnd();
	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	virtual void onFocus();
	virtual void onKillFocus();

	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

