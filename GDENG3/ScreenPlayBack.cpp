#include "ScreenPlayBack.h"

ScreenPlayBack::ScreenPlayBack(): AUIScreen("Screen Play Back")
{
}

void ScreenPlayBack::drawUI()
{
	ImGui::Begin("Screen Play Back");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1425, 25));
	//ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1024, 768));
	ImGui::SetWindowSize(ImVec2(290, UIManager::WINDOW_HEIGHT - 800));
	EngineBackEnd* backend = EngineBackEnd::getInstance();

	if (backend->getMode() == EngineBackEnd::EDITOR) 
	{
		if (ImGui::Button("Play")) { backend->setMode(EngineBackEnd::PLAY); }
	}
	else if (backend->getMode() != EngineBackEnd::EDITOR) 
	{
		if (ImGui::Button("Stop")) { backend->setMode(EngineBackEnd::EDITOR); }
	}

	ImGui::SameLine();

	if (backend->getMode() == EngineBackEnd::PLAY) 
	{
		if (ImGui::Button("Pause")) { backend->setMode(EngineBackEnd::PAUSED); }
	}
	else if (backend->getMode() == EngineBackEnd::PLAY) 
	{
		if (ImGui::Button("Resume")) { backend->setMode(EngineBackEnd::PLAY); }
	}
	else if (backend->getMode() == EngineBackEnd::PAUSED) 
	{
		if (ImGui::Button("Resume")) { backend->setMode(EngineBackEnd::PLAY); }
	}

	ImGui::SameLine();

	if (backend->getMode() == EngineBackEnd::PAUSED && ImGui::Button("Frame Step")) { backend->startFrameStep(); }
	ImGui::End();
}

ScreenPlayBack::~ScreenPlayBack()
{
}