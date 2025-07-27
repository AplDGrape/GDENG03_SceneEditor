#include "ScreenActions.h"

ScreenActions::ScreenActions() : AUIScreen("Actions")
{
}

void ScreenActions::drawUI()
{
	ImGui::Begin("Actions");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1425, 155));
	//ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1024, 768));
	ImGui::SetWindowSize(ImVec2(290, UIManager::WINDOW_HEIGHT - 800));

	if (ImGui::Button("Undo")) 
	{
		if (ActionHistory::getInstance()->hasRemainingUndoActions())
		{
			GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->undoAction());
		}

	}
	ImGui::SameLine();
	if (ImGui::Button("Redo")) 
	{
		if (ActionHistory::getInstance()->hasRemainingRedoActions())
		{
			GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->redoAction());
		}
	}
	ImGui::End();
}

ScreenActions::~ScreenActions()
{
}