#pragma once
#include <d3d11.h>

class Wireframe 
{
public:
    Wireframe(ID3D11Device* device);
    ~Wireframe();

    void set(ID3D11DeviceContext* context);

    void enable(ID3D11DeviceContext* context);
    void disable(ID3D11DeviceContext* context);
    void toggle();

    bool isEnabled() const;
private:
    ID3D11RasterizerState* m_wireframeState = nullptr;
    ID3D11RasterizerState* m_solidState = nullptr;
    bool m_enabled = false;
};