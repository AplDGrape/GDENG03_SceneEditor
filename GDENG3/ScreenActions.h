#pragma once
#include "AUIScreen.h"
#include "ActionHistory.h"
#include "UIManager.h"

#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_dx11.h"
#include "IMGUI\imgui_impl_win32.h"

class ScreenActions: public AUIScreen
{
public:
	ScreenActions();

	void drawUI() override;

	~ScreenActions();
};