#pragma once
#include "AUIScreen.h"

class DemoScreen : public AUIScreen
{
public:
    DemoScreen();
    ~DemoScreen();

    void drawUI() override;
};
