#include "Texture.h"
#include <DirectXTex.h>
#include "GraphicsEngine.h"

Texture::Texture(const wchar_t* full_path): Resource(full_path)
{
	DirectX::ScratchImage imageData;
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, imageData);

	if(SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(GraphicsEngine::getInstance()->getD3Ddevice(), imageData.GetImages(), imageData.GetImageCount(), imageData.GetMetadata(), &m_texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = imageData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)imageData.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsEngine::getInstance()->getD3Ddevice()->CreateShaderResourceView(m_texture, &desc, &shaderResView);
	}
	else
	{
		throw std::exception("Texture not created successfully");
	}
}

Texture::~Texture()
{
	this->m_texture->Release();
	this->shaderResView->Release();
}