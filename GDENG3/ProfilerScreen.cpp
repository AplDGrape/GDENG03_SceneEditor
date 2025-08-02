#include "ProfilerScreen.h"

ProfilerScreen::ProfilerScreen(): AUIScreen("Profile Screen")
{
}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("GDENG03 - Engine Profiler");
	//ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1425, 540));
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1435, 600));
	ImGui::SetWindowSize(ImVec2(290, UIManager::WINDOW_HEIGHT - 780));
	ImGui::Text("Application average framerate: %.3f \n Framerate:(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

ProfilerScreen::~ProfilerScreen()
{
}