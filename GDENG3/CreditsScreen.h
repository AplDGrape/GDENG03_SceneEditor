#pragma once
#include <d3d11.h>
#include "AUIScreen.h"
#include "UIManager.h"

#include "GraphicsEngine.h"
#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_dx11.h"
#include "IMGUI\imgui_impl_win32.h"

class CreditsScreen: public AUIScreen
{
public:
	CreditsScreen();

	void drawUI() override;
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

	~CreditsScreen();
private:
	int my_image_width = 0;
	int my_image_height = 0;
private:
	ID3D11ShaderResourceView* my_texture = NULL;

	bool ret;
};