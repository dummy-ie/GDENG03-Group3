#include "GeometryShader.h"
#include "GraphicsEngine.h"

GeometryShader::GeometryShader()
{
}

GeometryShader::~GeometryShader()
{
}

bool GeometryShader::release()
{
	m_gs->Release();
	delete this;

	return true;
}

bool GeometryShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreateGeometryShader(shader_byte_code, byte_code_size, nullptr, &m_gs)))
		return false;

	return true;
}
