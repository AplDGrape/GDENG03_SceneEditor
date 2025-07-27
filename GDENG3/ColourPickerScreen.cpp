#include "ColourPickerScreen.h"

ColourPickerScreen::ColourPickerScreen(): AUIScreen("Color Picker")
{
}

void ColourPickerScreen::drawUI()
{
	ImGui::Begin("Color Picker Screen", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1125, 480));

	// Colour Wheel
	ImGui::ColorPicker4("##ColorWheel", (float*)&UIManager::logoTint,
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
	ImGui::SameLine();

	// Colour display & close
	ImGui::BeginGroup();
	ImGui::Text("Color");
	ImGui::ColorButton("Current Color", UIManager::logoTint, ImGuiColorEditFlags_NoTooltip, ImVec2(65, 35));
	ImGui::Dummy(ImVec2(0, 30));

	float padding = 10.0f;
	ImVec2 buttonSize = ImVec2(70.0f, 0.0f);
	float buttonX = ImGui::GetWindowContentRegionMax().x - buttonSize.x - padding;

	ImGui::SetCursorPosX(buttonX);

	if (ImGui::Button("Close", buttonSize)) {
		UIManager::getInstance()->hideColorPickerScreen();
	}
	ImGui::EndGroup();

	ImGui::End();
}

ColourPickerScreen::~ColourPickerScreen()
{
}