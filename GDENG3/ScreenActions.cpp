#include "ScreenActions.h"

ScreenActions::ScreenActions() : AUIScreen("Actions")
{
}

void ScreenActions::drawUI()
{
	ImGui::Begin("Actions");
	//ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1425, 130));
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1435, 85));
	ImGui::SetWindowSize(ImVec2(100, 60));

	if (ImGui::Button("Undo")) 
	{
		if (ActionHistory::getInstance()->hasRemainingUndoActions())
		{
			GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->undoAction());
			std::cout << "[Action] Undo performed\n";
		}
		else
		{
			std::cout << "[Action] No more actions to undo\n";
		}

	}
	ImGui::SameLine();
	if (ImGui::Button("Redo")) 
	{
		if (ActionHistory::getInstance()->hasRemainingRedoActions())
		{
			GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->redoAction());
			std::cout << "[Action] Redo performed\n";
		}
		else
		{
			std::cout << "[Action] No more actions to redo\n";
		}
	}
	ImGui::End();
}

ScreenActions::~ScreenActions()
{
}