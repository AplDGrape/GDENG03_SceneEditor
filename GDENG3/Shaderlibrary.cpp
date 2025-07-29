#include "Shaderlibrary.h"

Shaderlibrary* Shaderlibrary::sharedInstance = NULL;

Shaderlibrary::Shaderlibrary()
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	ShaderData shaderdata;
	ShaderNames names;

	// Base Shader
	graphEngine->compileVertexShader(names.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	this->activeVertexShaders[names.BASE_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderdata.shaderByteCode, shaderdata.sizeShader);

	graphEngine->compilePixelShader(names.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	this->activePixelShaders[names.BASE_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderdata.shaderByteCode, shaderdata.sizeShader);

	// Texture Shader
	graphEngine->compileVertexShader(names.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	this->activeVertexShaders[names.TEXTURED_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderdata.shaderByteCode, shaderdata.sizeShader);

	graphEngine->compilePixelShader(names.TEXTURED_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	this->activePixelShaders[names.TEXTURED_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderdata.shaderByteCode, shaderdata.sizeShader);

	// Mesh Shader
	graphEngine->compilePixelShader(names.MESHLAYOUT_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	this->activePixelShaders[names.MESHLAYOUT_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderdata.shaderByteCode, shaderdata.sizeShader);

	graphEngine->compileVertexShader(names.MESHLAYOUT_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	this->activeVertexShaders[names.MESHLAYOUT_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderdata.shaderByteCode, shaderdata.sizeShader);
	::memcpy(m_mesh_layout_byte_code, shaderdata.shaderByteCode, shaderdata.sizeShader);
	m_mesh_layout_size = shaderdata.sizeShader;
}

Shaderlibrary* Shaderlibrary::getInstance()
{
	return sharedInstance;
}

void Shaderlibrary::initialize()
{
	sharedInstance = new Shaderlibrary();
}

void Shaderlibrary::destroy()
{
	delete sharedInstance;
}

void Shaderlibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	ShaderNames names;
	ShaderData shaderdata;

	// Base
	if(vertexShaderName == names.BASE_VERTEX_SHADER_NAME)
	{
		graphEngine->compileVertexShader(names.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", shaderByteCode, sizeShader);
		
	}
	// Textured
	else if(vertexShaderName == names.TEXTURED_VERTEX_SHADER_NAME)
	{
		graphEngine->compileVertexShader(names.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", shaderByteCode, sizeShader);
	}
	// Mesh
	else if(vertexShaderName == names.MESHLAYOUT_VERTEX_SHADER_NAME)
	{
		graphEngine->compileVertexShader(names.MESHLAYOUT_VERTEX_SHADER_NAME.c_str(), "vsmain", shaderByteCode, sizeShader);
		*shaderByteCode = m_mesh_layout_byte_code;
		*sizeShader = m_mesh_layout_size;
	}
}

void Shaderlibrary::requestPixelShaderData(String pixelShaderName, void** shaderByteCode, size_t* sizeShader)
{
}

VertexShader* Shaderlibrary::getVertexShader(String vertexShaderName)
{
	return this->activeVertexShaders.at(vertexShaderName);
}

PixelShader* Shaderlibrary::getPixelShader(String pixelShaderName)
{
	return this->activePixelShaders.at(pixelShaderName);
}

Shaderlibrary::~Shaderlibrary()
{
	ShaderNames names;

	this->activeVertexShaders[names.BASE_VERTEX_SHADER_NAME]->release();
	this->activePixelShaders[names.BASE_PIXEL_SHADER_NAME]->release();
	this->activeVertexShaders[names.MESHLAYOUT_VERTEX_SHADER_NAME]->release();
	this->activePixelShaders[names.MESHLAYOUT_PIXEL_SHADER_NAME]->release();

	this->activePixelShaders.clear();
	this->activeVertexShaders.clear();
}
