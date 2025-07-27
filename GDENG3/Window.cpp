#ifndef UNICODE
#define UNICODE
#endif

#include "Window.h"
#include <iostream>
#include "IMGUI/imgui.h"

using namespace std;

//Declared for handling mouse and key events in IMGUI
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Window* window = nullptr;
Window::Window()
{
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch (msg)
	{
		case WM_CREATE:
		{
			//Event fired when the window is created
			//Collected here..
			Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
			//..and then stored for later lookup
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
			window->setHWND(hwnd);

			window->onCreate();
			break;
		}
		case WM_DESTROY:
		{
			//Event fired when the window is destroyed
			Window* window = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			::PostQuitMessage(0);
			break;
		}
		case WM_SETFOCUS:
		{
			//Event fired when the window get focus
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onFocus();
			//::PostQuitMessage(0);
			break;
		}
		case WM_KILLFOCUS:
		{
			//Event fired when the window lost focus
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onKillFocus();
			//::PostQuitMessage(0);
			break;
		}
		default:
		{
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &wndProc;

	if (!::RegisterClassEx(&wc)) // If the registration of class will fail, the function will return false
		return false;

	//Creation of window
	this->m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1440, 900, NULL, NULL, NULL, this);
	//this->m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	//If the creation fail returns false
	if (!this->m_hwnd)
		return false;

	//Show up the window
	::ShowWindow(this->m_hwnd, SW_SHOW);
	::UpdateWindow(this->m_hwnd);

	/*if (!window)
		window = this;*/

	//Set this flag ro true to indicate that the window is initialized and running
	m_is_run = true;

	return true;
}

bool Window::broadcast()
{
	//EngineTime::LogFrameStart();

	MSG msg;
	EngineTime::LogFrameStart();
	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//this->onUpdate();

	Sleep(1);

	EngineTime::LogFrameEnd();

	return true;
}

bool Window::release()
{
	//Destroy the window
	if (!::DestroyWindow(this->m_hwnd))
		return false;

	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

HWND Window::gethwnd()
{
	return m_hwnd;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);

	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	m_is_run = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}

Window::~Window()
{

}