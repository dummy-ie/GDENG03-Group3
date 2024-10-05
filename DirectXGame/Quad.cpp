#include "Quad.h"

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

Quad::Quad(const Vec2 size, const Vec2 pos, const Vec2 pos1, const Vec3 color) : size(size), pos(pos), color(color)
{
	Vertex list[] =
	{
		{
			{-size.x + pos.x, -size.y + pos.y, 0.0f},
			{-size.x + pos1.x, -size.y + pos1.y, 0.0f},
			color,
			{0, 1, 0}},

		{
			{-size.x + pos.x, size.y + pos.y, 0.0f},
			{-size.x + pos1.x, size.y + pos1.y, 0.0f},
			color,
			{	0, 1, 1}},

		{
			{size.x + pos.x, -size.y + pos.y, 0.0f},
			{size.x + pos1.x, -size.y + pos1.y, 0.0f},
			color,
			{	1, 0, 0}},

		{
			{size.x + pos.x, size.y + pos.y, 0.0f},
			{size.x + pos1.x, size.y + pos1.y, 0.0f},
			color,
			{0, 0, 1}}
	};

	void* shader_byte_code = nullptr;
	size_t byte_code_size = 0;

	vb = GraphicsEngine::get()->createVertexBuffer();
	constexpr UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, byte_code_size);
	vb->load(list, sizeof(Vertex), size_list, shader_byte_code, static_cast<UINT>(byte_code_size));
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compileGeometryShader(L"GeometryShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	gs = GraphicsEngine::get()->createGeometryShader(shader_byte_code, byte_code_size);
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, byte_code_size);
	GraphicsEngine::get()->releaseCompiledShader();

	Constant cc;
	//cc.time = 0;

	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(Constant));
}

Quad::Quad(Vertex list[], int size_list)
{
	void* shader_byte_code = nullptr;
	size_t byte_code_size = 0;

	vb = GraphicsEngine::get()->createVertexBuffer();
	//constexpr UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, byte_code_size);
	vb->load(list, sizeof(Vertex), size_list, shader_byte_code, static_cast<UINT>(byte_code_size));
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compileGeometryShader(L"GeometryShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	gs = GraphicsEngine::get()->createGeometryShader(shader_byte_code, byte_code_size);
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, byte_code_size);
	GraphicsEngine::get()->releaseCompiledShader();

	Constant cc;
	//cc.time = 0;

	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(Constant));
}

void Quad::release() const
{
	vb->release();
	vs->release();
	ps->release();
}

void Quad::draw(float deltaTime)
{
	this->angle += 1.57f * deltaTime;

	Constant cc;
	cc.angle = angle;

	cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(gs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb->getSizeVertexList(), 0);
}
