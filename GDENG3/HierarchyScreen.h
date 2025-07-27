#pragma once
#include "AUIScreen.h"
#include "UIManager.h"

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"

class HierarchyScreen: public AUIScreen
{
public:
	HierarchyScreen();

	void drawUI() override;

	~HierarchyScreen();
private:
	void generateButtons();
};