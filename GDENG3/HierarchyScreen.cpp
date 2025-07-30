#include "HierarchyScreen.h"

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
	std::vector<AGameObject*> allObjects = manager->getAllObjects();

	for (AGameObject* obj : allObjects)
	{
		if (obj->getParent() == nullptr) {
			drawObjectHierarchyRecursive(obj, manager);
		}
	}
}

void HierarchyScreen::drawObjectHierarchyRecursive(AGameObject* obj, GameObjectManager* manager)
{
    ImGui::PushID(obj->getName().c_str());

    bool isSelected = (manager->getSelectedObject() == obj);
    ImGuiTreeNodeFlags flags = isSelected ? ImGuiTreeNodeFlags_Selected : 0;
    if (obj->getChildren().empty()) flags |= ImGuiTreeNodeFlags_Leaf;

    bool open = ImGui::TreeNodeEx(obj->getName().c_str(), flags);
    if (ImGui::IsItemClicked()) 
    {
        manager->setSelectedObject(obj);
    }

    // Drag & Drop Source
    if (ImGui::BeginDragDropSource()) 
    {
        ImGui::SetDragDropPayload("GAMEOBJECT_DRAG", obj->getName().c_str(), obj->getName().size() + 1);
        ImGui::Text("Dragging: %s", obj->getName().c_str());
        ImGui::EndDragDropSource();
    }

    // Drag & Drop Target
    if (ImGui::BeginDragDropTarget()) 
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT_DRAG")) 
        {
            std::string draggedName = (const char*)payload->Data;
            AGameObject* dragged = manager->findObjectByName(draggedName);

            if (dragged && dragged != obj && !dragged->hasPhysics() && !dragged->isAncestorOf(obj)) 
            {
                dragged->setParent(obj);
            }
        }
        ImGui::EndDragDropTarget();
    }

    if (open) 
    {
        for (AGameObject* child : obj->getChildren()) 
        {
            drawObjectHierarchyRecursive(child, manager);
        }

        ImGui::TreePop();
    }

    ImGui::PopID();
}