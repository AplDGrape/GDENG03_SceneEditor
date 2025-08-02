#include "EditorScreen.h"
#include "InspectorScreen.h"
#include "HierarchyScreen.h"

EditorScreen::EditorScreen(): AUIScreen("EditorScreen")
{
    inspector = new InspectorScreen();
    hierarchy = new HierarchyScreen();
}

EditorScreen::~EditorScreen()
{
    delete inspector;
    delete hierarchy;
}

void EditorScreen::drawUI()
{
    ImGui::Begin("Scene Editor", nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2(775, 25));
    ImGui::SetWindowSize(ImVec2(225, UIManager::WINDOW_HEIGHT - 205));

    if (ImGui::BeginTabBar("EditorTabs"))
    {
        if (ImGui::BeginTabItem("Hierarchy"))
        {
            hierarchy->drawUI();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Inspector"))
        {
            inspector->drawUI();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}
