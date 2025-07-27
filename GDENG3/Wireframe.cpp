#include "Wireframe.h"

Wireframe::Wireframe(ID3D11Device* device)
{
    //Wireframe
    D3D11_RASTERIZER_DESC desc = {};
    desc.FillMode = D3D11_FILL_WIREFRAME;
    desc.CullMode = D3D11_CULL_BACK;
    desc.DepthClipEnable = TRUE;
    device->CreateRasterizerState(&desc, &m_wireframeState);

    desc.FillMode = D3D11_FILL_SOLID;
    device->CreateRasterizerState(&desc, &m_solidState);
}

Wireframe::~Wireframe()
{
    if (m_wireframeState) m_wireframeState->Release();
    if (m_solidState) m_solidState->Release();
}

void Wireframe::set(ID3D11DeviceContext* context)
{
    context->RSSetState(m_enabled ? m_wireframeState : m_solidState);
}

void Wireframe::enable(ID3D11DeviceContext* context)
{
    m_enabled = true;
    context->RSSetState(m_wireframeState);
}

void Wireframe::disable(ID3D11DeviceContext* context)
{
    m_enabled = false;
    context->RSSetState(m_solidState);
}

void Wireframe::toggle()
{
    m_enabled = !m_enabled;
}

bool Wireframe::isEnabled() const
{
    return m_enabled;
}