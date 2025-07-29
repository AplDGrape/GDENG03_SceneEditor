#pragma once
#include "AUIScreen.h"
#include "UIManager.h"
#include "Wireframe.h"
#include "AppWindow.h"

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"

class DebugConsoleScreen final : public AUIScreen
{
public:
	DebugConsoleScreen();

	void drawUI() override;

	~DebugConsoleScreen();
};