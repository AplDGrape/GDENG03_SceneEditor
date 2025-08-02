#pragma once
#include "AUIScreen.h"

class InspectorScreen;
class HierarchyScreen;

class EditorScreen : public AUIScreen
{
public:
    EditorScreen();
    ~EditorScreen();

    void drawUI() override;

private:
    InspectorScreen* inspector;
    HierarchyScreen* hierarchy;
};
