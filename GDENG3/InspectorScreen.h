#pragma once
#include "UIManager.h"
#include "AUIScreen.h"

#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_dx11.h"
#include "IMGUI\imgui_impl_win32.h"

class InspectorScreen: public AUIScreen
{
public:
	InspectorScreen();

	void drawUI() override;
	void generateEditor();
	void onTransformUpdate();
	void TransformSelected(AGameObject* selected);

	~InspectorScreen();
private:
	float SelectedObjectposition[3] = { 0.0f, 0.0f, 0.0f };
	float SelectedObjectScale[3] = { 0.0f, 0.0f, 0.0f };
	float SelectedObjectRotation[3] = { 0.0f, 0.0f, 0.0f };
private:
	ImGui::FileBrowser* textureDialogue;
};