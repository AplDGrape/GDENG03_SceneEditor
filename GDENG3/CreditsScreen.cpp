#include "CreditsScreen.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

CreditsScreen::CreditsScreen():AUIScreen("Credits Screen")
{
	bool ret = LoadTextureFromFile("Images/DLSU_logo.jpg", &my_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);
}

void CreditsScreen::drawUI()
{
    ImGuiStyle& style = ImGui::GetStyle();

    if (ImGui::Begin("Credits"))
    {
        float width = ImGui::GetWindowSize().x;
        float centre_position_for_button = (width - ImVec2(70.0f, 0.0f).x) / 2;
        ImGui::SetCursorPosX(centre_position_for_button);

        ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1125, 25));
        ImGui::SetWindowSize(ImVec2(550, UIManager::WINDOW_HEIGHT - 450));
        //ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height));
        ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height), ImVec2(0, 0), ImVec2(1, 1), UIManager::logoTint);
        ImGui::Text("About");
        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
        ImGui::Text("Scene Editor v2.3");
        ImGui::Text("Developed by: Francis Raphael D. Apolinar");
        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
        ImGui::Text("Acknowledgements:");
        ImGui::Separator();
        ImGui::Text("PardCode Game Engine Tutorial");
        ImGui::Text("Sir Neil's GAMENG3 Course");
        ImGui::Text("The ImGui API is from 'https://github.com/ocornut/imgui'");
        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Separator();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 80.0f) / 2.0f); // center button
        /*if (ImGui::Button("Close", ImVec2(80, 0)))
        {
            //m_showCredits = false;
            UIManager::getInstance()->hideCreditsScreen();
        }*/
    }

	ImGui::End();
}

bool CreditsScreen::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);

    if (image_data == NULL)
    {
        std::cout << "Failed to get image\n";
        return false;

    }
        
    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    GraphicsEngine::getInstance()->getD3Ddevice()->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    GraphicsEngine::getInstance()->getD3Ddevice()->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

CreditsScreen::~CreditsScreen()
{
}