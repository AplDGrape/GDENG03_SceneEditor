#pragma once
#include "Window.h"
#include "AUIScreen.h"

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class UINames
{
public:
	const String PROFILER_SCREEN = "PROFILER_SCREEN";
	const String MENU_SCREEN = "MENU_SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String COLOURPICKER_SCREEN = "COLOURPICKER_SCREEN";
	const String DEMO_SCREEN = "DEMO_SCREEN";
	const String PLAYBACK_SCREEN = "PLAYBACK_SCREEN";
	const String ACTIONS_SCREEN = "ACTIONS_SCREEN";
	const String DEBUG_CONSOLE_SCREEN = "DEBUG_CONSOLE_SCREEN";
};