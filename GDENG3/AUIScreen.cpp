#include "AUIScreen.h"

AUIScreen::AUIScreen(String name)
{
	this->name = name;
}

String AUIScreen::getName()
{
	return this->name;
}

AUIScreen::~AUIScreen()
{
}