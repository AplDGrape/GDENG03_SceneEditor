#include "VertexBufferTextured.h"

VertexBufferTextured::VertexBufferTextured()
{
	this->m_layout = 0;
	this->m_buffer = 0;
}

bool VertexBufferTextured::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
	if (this->m_buffer)this->m_buffer->Release();

	if (this->m_layout)this->m_layout->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list;


	if (FAILED(GraphicsEngine::getInstance()->getD3Ddevice()->CreateBuffer(&buff_desc, &init_data, &this->m_buffer)))
	{
		std::cout << "Failed to create vertex buffer";
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA , 0}
	};

	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(GraphicsEngine::getInstance()->getD3Ddevice()->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &this->m_layout)))
	{
		std::cout << "Failed to create input layout";
		return false;
	}

	return true;
}

bool VertexBufferTextured::release()
{
	this->m_layout->Release();
	this->m_buffer->Release();
	delete this;

	return true;
}

ID3D11Buffer* VertexBufferTextured::getBuffer()
{
	return this->m_buffer;
}

ID3D11InputLayout* VertexBufferTextured::getLayout()
{
	return this->m_layout;
}

UINT VertexBufferTextured::getSizeVertexBuffer()
{
	return this->m_size_vertex;
}

UINT VertexBufferTextured::getSizeVertexList()
{
	return this->m_size_list;
}

VertexBufferTextured::~VertexBufferTextured()
{
	this->m_layout->Release();
	this->m_buffer->Release();
}