#pragma once
#include "AUIScreen.h"
#include "EngineBackEnd.h"
#include "UIManager.h"

#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_dx11.h"
#include "IMGUI\imgui_impl_win32.h"

class ScreenPlayBack : public AUIScreen
{
public:
	ScreenPlayBack();

	void drawUI() override;

	~ScreenPlayBack();
};