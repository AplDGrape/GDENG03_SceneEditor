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
	const auto& allObjects = manager->getAllObjects();

	for (AGameObject* obj : allObjects)
	{
		if (obj->getParent() == nullptr)
		{
			drawObjectNodeRecursive(obj);
		}
	}
}

void HierarchyScreen::drawObjectNodeRecursive(AGameObject* obj)
{
	GameObjectManager* manager = GameObjectManager::getInstance();

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
	if (manager->getSelectedObject() == obj)
		flags |= ImGuiTreeNodeFlags_Selected;

	bool open = ImGui::TreeNodeEx(obj->getName().c_str(), flags);

	// Selection
	if (ImGui::IsItemClicked())
		manager->setSelectedObject(obj->getName());

	// Drag source
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("PARENTING_OP", &obj, sizeof(AGameObject*));
		ImGui::Text("Dragging %s", obj->getName().c_str());
		ImGui::EndDragDropSource();
	}

	// Drop target
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PARENTING_OP"))
		{
			AGameObject* dragged = *(AGameObject**)payload->Data;
			if (dragged != obj && !isDescendantOf(obj, dragged)) // prevent loops
			{
				dragged->setParentPreserveWorld(obj);
			}
		}
		ImGui::EndDragDropTarget();
	}

	if (open)
	{
		for (AGameObject* child : obj->getChildren())
		{
			drawObjectNodeRecursive(child);
		}
		ImGui::TreePop();
	}
}

bool HierarchyScreen::isDescendantOf(AGameObject* parent, AGameObject* child)
{
	for (AGameObject* c : parent->getChildren())
	{
		if (c == child || isDescendantOf(c, child))
			return true;
	}
	return false;
}
