#include "DeviceContext.h"
#include "SwapChain.h"	

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context)
{
	this->m_device_context = device_context;
}

ID3D11DeviceContext* DeviceContext::getContext()
{
	return this->m_device_context;
}


bool DeviceContext::release()
{
	this->m_device_context->Release();
	delete this;
	return true;
}

void DeviceContext::clearRenderTargetColor(SwapChain* swapchain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha };
	ID3D11RenderTargetView* renderview = swapchain->getRenderTargetView();
	ID3D11DepthStencilView* depthview = swapchain->getDepthStencilView();
	this->m_device_context->ClearRenderTargetView(renderview, clear_color);
	this->m_device_context->ClearDepthStencilView(depthview, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	this->m_device_context->OMSetRenderTargets(1, &renderview, depthview);
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->getSizeVertexBuffer();
	UINT offset = 0;

	this->m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	this->m_device_context->IASetInputLayout(vertex_buffer->m_layout);
}

void DeviceContext::setVertexBufferTextured(VertexBufferTextured* textured_vertex_buffer)
{
	UINT stride = textured_vertex_buffer->getSizeVertexBuffer();
	UINT offset = 0;

	this->m_device_context->IASetVertexBuffers(0, 1, &textured_vertex_buffer->m_buffer, &stride, &offset);
	this->m_device_context->IASetInputLayout(textured_vertex_buffer->m_layout);
}

void DeviceContext::setIndexBuffer(IndexBuffer* index_buffer)
{
	this->m_device_context->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::setVertexShader(VertexShader* vertex_shader)
{
	this->m_device_context->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}

void DeviceContext::setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* constant_buffer)
{
	this->m_device_context->VSSetConstantBuffers(0, 1, &constant_buffer->m_buffer);
}

void DeviceContext::setTexture(VertexShader* vertex_shader, Texture* texture)
{
	//this->m_device_context->VSSetShaderResources(0, 1, &texture->shaderResView);
	if (texture)
	{
		this->m_device_context->VSSetShaderResources(0, 1, &texture->shaderResView);
	}
	else
	{
		ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
		this->m_device_context->VSSetShaderResources(0, 1, nullSRV);
	}
}

void DeviceContext::setPixelShader(PixelShader* pixel_shader)
{
	this->m_device_context->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DeviceContext::setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* constant_buffer)
{
	this->m_device_context->PSSetConstantBuffers(0, 1, &constant_buffer->m_buffer);
}

void DeviceContext::setTexture(PixelShader* pixel_shader, Texture* texture)
{
	//this->m_device_context->PSSetShaderResources(0, 1, &texture->shaderResView);
	if (texture)
	{
		this->m_device_context->PSSetShaderResources(0, 1, &texture->shaderResView);
	}
	else
	{
		ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
		this->m_device_context->PSSetShaderResources(0, 1, nullSRV);
	}
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	this->m_device_context->RSSetViewports(1, &viewport);
}



void DeviceContext::drawTriangleList(UINT vertex_count, UINT startVertexIndex)
{
	this->m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_device_context->Draw(vertex_count, startVertexIndex);
}

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	this->m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT startVertexIndex)
{
	this->m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->m_device_context->Draw(vertex_count, startVertexIndex);
}

DeviceContext::~DeviceContext()
{
}

