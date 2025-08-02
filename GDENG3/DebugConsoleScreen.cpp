#include "DebugConsoleScreen.h"
#include "Debug.h"

DebugConsoleScreen::DebugConsoleScreen() : AUIScreen("Debug Console Screen")
{
}

void DebugConsoleScreen::drawUI()
{
	ImGui::Begin(name.c_str());
	//ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1125, 505));
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1142.5, 600));
	ImGui::SetWindowSize(ImVec2(475, 120));
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

	auto messageList = Debug::GetInstance().GetMessageList(Debug::LogLevel::None);

	static int lastMessageCount = 0;
	bool scrollToBottom = false;

	// Check if a new message has been added
	if ((int)messageList.size() > lastMessageCount)
	{
		scrollToBottom = true;
		lastMessageCount = (int)messageList.size();
	}

	for (auto& message : messageList)
	{
		ImGui::Text(message.Message.c_str());
	}

	if (scrollToBottom)
		ImGui::SetScrollHereY(1.0f);

	ImGui::EndChild();
	ImGui::End();
}

DebugConsoleScreen::~DebugConsoleScreen()
{

}
