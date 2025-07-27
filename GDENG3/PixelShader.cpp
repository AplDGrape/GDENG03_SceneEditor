#include "PixelShader.h"

PixelShader::PixelShader()
{
}

void PixelShader::release()
{
	this->m_ps->Release();
	delete this;
}

bool PixelShader::init(const void* shader_byte, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::getInstance()->getD3Ddevice()->CreatePixelShader(shader_byte, byte_code_size, nullptr, &this->m_ps))) 
	{
		std::cout << "Failed to create pixel shader";
		return false;
	}
	return true;
}

PixelShader::~PixelShader()
{
}