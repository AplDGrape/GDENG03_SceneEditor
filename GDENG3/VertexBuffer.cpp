#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
	this->m_layout = 0;
	this->m_buffer = 0;
}

bool VertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
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
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		/*{"POSITION", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},*/
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(GraphicsEngine::getInstance()->getD3Ddevice()->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &this->m_layout)))
	{
		std::cout << "Failed to create input layout";
		return false;
	}

	return true;
}

UINT VertexBuffer::getSizeVertexBuffer()
{
	return this->m_size_vertex;
}

UINT VertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}

ID3D11Buffer* VertexBuffer::getBuffer()
{
	return this->m_buffer;
}

ID3D11InputLayout* VertexBuffer::getLayout()
{
	return this->m_layout;
}

bool VertexBuffer::release()
{
	this->m_layout->Release();
	this->m_buffer->Release();
	delete this;

	return true;
}

VertexBuffer::~VertexBuffer()
{
}