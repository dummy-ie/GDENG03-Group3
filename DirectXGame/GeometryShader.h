#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class GeometryShader
{
public:
	GeometryShader();
	~GeometryShader();
	bool release();

private:
	bool init(const void* shader_byte_code, size_t byte_code_size);

	ID3D11GeometryShader* m_gs;

	friend class GraphicsEngine;
	friend class DeviceContext;

};

