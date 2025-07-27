#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

#include "IMGUI/imgui.h"
#include "IMGUI/imfilebrowser.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"

#include <iostream>

class MenuScreen: public AUIScreen
{
public:
	MenuScreen();
	void drawUI() override;

	~MenuScreen();

	bool isOpen = false;

	bool openSceneSelected = false;
public:
	ImGui::FileBrowser* saveSceneDialog;
	ImGui::FileBrowser* openSceneDialog;

	ImGui::FileBrowser* objDialog;
	ImGui::FileBrowser* textureDialogue;

private:
	String OBJname;
	Mesh* mesh;
	Texture* text;
};