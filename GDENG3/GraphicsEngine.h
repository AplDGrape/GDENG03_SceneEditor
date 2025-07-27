#pragma once
#include <d3d11.h>

#include "GraphicsEngine.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexBufferTextured.h"

#include "VertexShader.h"
#include "PixelShader.h"

class SwapChain;
class DeviceContext;
class VertexBuffer;
class ConstantBuffer;
class IndexBuffer;
class VertexBufferTextured;

class GraphicsEngine
{
public:
	//Initialize the GraphicsEngine and DirectX 11 Device
	bool init();

	bool compileVertexShader(const wchar_t* Filename, const char* EntryPointName, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* Filename, const char* EntryPointName, void** shader_byte_code, size_t* byte_code_size);

	void releaseCompiledShader();

	//DEFAULT SIMPLE SHADERS
	//bool createShaders();
	//bool setShaders();
	//void getShaderBufferAndSize(void** bytecode, UINT* size);

	//Release all the resources loaded
	bool release();
public:
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();

	VertexBuffer* createVertexBuffer();
	VertexBufferTextured* createTexturedVertexBuffer();
	IndexBuffer* createIndexBuffer();
	ConstantBuffer* createConstantBuffer();

	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
public:
	static GraphicsEngine* getInstance();
	static void initialize();
	static void destroy();
private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&){};
	GraphicsEngine&operator=(GraphicsEngine const&){};
//wireframe
public:
	ID3D11Device* getD3DDevice();
	ID3D11DeviceContext* getD3DDeviceContext();
private:
	static GraphicsEngine* sharedInstance;
private:
	DeviceContext* m_imm_device_context;

public:
	ID3D11Device* getD3Ddevice();
	D3D_FEATURE_LEVEL getFeatureLevel();
	IDXGIFactory* getFactory();
private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	
	ID3D11DeviceContext* m_imm_context;
private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
private:
	ID3DBlob* m_blob = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
private:
	friend class SwapChain;
	friend class ConstantBuffer;
	friend class IndexBuffer;
};