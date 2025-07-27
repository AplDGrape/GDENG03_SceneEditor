#include "HierarchyScreen.h"
#include "GameObjectManager.h"

HierarchyScreen::HierarchyScreen():AUIScreen("HierarchyScreen")
{
}

void HierarchyScreen::drawUI()
{
	ImGui::Begin("Scene Outliner");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 525, 25));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
	this->generateButtons();
	ImGui::End();
}

HierarchyScreen::~HierarchyScreen()
{
}

void HierarchyScreen::generateButtons()
{
	GameObjectManager* manager = GameObjectManager::getInstance();

	for(int i = 0; i < GameObjectManager::getInstance()->activeObjects(); i++)
	{
		if (ImGui::Button(manager->getAllObjects()[i]->getName().c_str(), ImVec2(160.0f, 0.0f)))
		{
			AGameObject* selectedObject = manager->getAllObjects()[i];
			manager->setSelectedObject(selectedObject->getName());
		}
		
	}
}