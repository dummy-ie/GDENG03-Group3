#pragma once
#include "Component.h"
#include <Windows.h>

#include "Material.h"

class Renderer3D final : public Component
{
public:
	explicit Renderer3D(
		std::string name,
		GameObject* owner,
		const MeshPtr& mesh,
		const MaterialPtr& mat,
		const std::wstring& vs = L"VertexShader.hlsl",
		const std::wstring& gs = L"GeometryShader.hlsl"
		);

	void update() override;

private:
	VertexShaderPtr vertexShader = nullptr;
	GeometryShaderPtr geometryShader = nullptr;
	MaterialPtr material = nullptr;

	MeshPtr mesh = nullptr;

	VertexBufferPtr vertexBuffer = nullptr;
	IndexBufferPtr indexBuffer = nullptr;
	ConstantBufferPtr constantBuffer = nullptr;
};

