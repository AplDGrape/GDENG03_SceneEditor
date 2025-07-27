#pragma once
#include <iostream>
#include "InputListener.h"
#include <vector>
#include <Windows.h>
#include <unordered_set>



class InputSystem
{
public:

	typedef std::vector<InputListener*> List;

	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void update();

	void setCursorPosition(const Point& position);
	void showCursor(bool show);

	bool isKeyDown(int key);
	bool isKeyUp(int key);

	void callOnKeyDown(int key);
	void callOnKeyUp(int key);

	void callOnMouseMove(Point delta);

	void callOnLeftMouseDown(Point delta);
	void callOnRightMouseDown(Point delta);

	void callOnLeftMouseUp(Point delta);
	void callOnRightMouseUp(Point delta);

private:
	static InputSystem* sharedInstance;
	List InputListeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point oldMousePosition;
	bool firstTime = true;

private:
	InputSystem();
	~InputSystem();


};

