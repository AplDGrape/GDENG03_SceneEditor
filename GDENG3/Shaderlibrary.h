#pragma once
#include "VertexShader.h"
#include "PixelShader.h"

#include <unordered_map>

class VertexShader;
class PixelShader;

class ShaderNames
{
public:
	typedef std::wstring String;

	// Vertex shader names
	const String BASE_VERTEX_SHADER_NAME = L"VertexShader.hlsl";
	const String TEXTURED_VERTEX_SHADER_NAME = L"TexturedVertexShader.hlsl";
	const String MESHLAYOUT_VERTEX_SHADER_NAME = L"VertexMeshLayoutShader.hlsl";

	// Pixel shader names
	const String BASE_PIXEL_SHADER_NAME = L"PixelShader.hlsl";
	const String TEXTURED_PIXEL_SHADER_NAME = L"TexturedPixelShader.hlsl";
	const String MESHLAYOUT_PIXEL_SHADER_NAME = L"PixelMeshLayoutShader.hlsl";
};

class Shaderlibrary
{
public:
	class ShaderData
	{
	public:
		void* shaderByteCode = NULL;
		size_t sizeShader = 0;
	};

	typedef std::wstring String;
	typedef std::unordered_map<String, VertexShader*> VertexShaderTable;
	typedef std::unordered_map<String, PixelShader*> PixelShaderTable;

	static Shaderlibrary* getInstance();
	static void initialize();
	static void destroy();

	// Since shader byte code gets dereferenced for some reason if stored in a hash table. request manually.
	void requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader);
	void requestPixelShaderData(String pixelShaderName, void** shaderByteCode, size_t* sizeShader);

	VertexShader* getVertexShader(String vertexShaderName);
	PixelShader* getPixelShader(String pixelShaderName);
private:
	Shaderlibrary();
	~Shaderlibrary();

	Shaderlibrary(Shaderlibrary const&) {};
	Shaderlibrary& operator=(Shaderlibrary const&) {};
	static Shaderlibrary* sharedInstance;
private:
	VertexShaderTable activeVertexShaders;
	PixelShaderTable activePixelShaders;
private:
	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};