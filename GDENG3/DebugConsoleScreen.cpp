#include "DebugConsoleScreen.h"
#include "Debug.h"

DebugConsoleScreen::DebugConsoleScreen() : AUIScreen("Debug Console Screen")
{
}

void DebugConsoleScreen::drawUI()
{
	ImGui::Begin(name.c_str());

	auto messageList = Debug::GetInstance().GetMessageList(Debug::LogLevel::None);

	for (auto& message : messageList)
	{
		ImGui::Text(message.Message.c_str());
	}

	Wireframe* wf = AppWindow::getInstance()->getWireframe();
	if (wf)
		ImGui::Text("Wireframe Mode: %s", wf->isEnabled() ? "ON" : "OFF");

	ImGui::End();
}

DebugConsoleScreen::~DebugConsoleScreen()
{

}
