#include "DemoScreen.h"
#include "IMGUI/imgui.h"

DemoScreen::DemoScreen() : AUIScreen("Demo Screen") {}

DemoScreen::~DemoScreen() {}

void DemoScreen::drawUI()
{
    ImGui::ShowDemoWindow();
}
