#pragma once
#include "Component.h"
#include <Windows.h>

#include "Material.h"

namespace gdeng03
{
	class Renderer3D final : public Component
	{
	public:
		explicit Renderer3D(
			GameObject* owner,
			MeshPtr mesh,
			const MaterialPtr& mat = nullptr,
			const std::wstring& vs = L"VertexShader.hlsl",
			const std::wstring& gs = L"GeometryShader.hlsl"
		);

		void update() override;
		Material* getMaterial() const;
		Mesh* getMesh() const;
		void createMaterial();
		void resetMaterial();

	private:
		VertexShaderPtr vertexShader = nullptr;
		GeometryShaderPtr geometryShader = nullptr;
		MaterialPtr material = nullptr;

		MeshPtr mesh = nullptr;

		VertexBufferPtr vertexBuffer = nullptr;
		IndexBufferPtr indexBuffer = nullptr;
		ConstantBufferPtr constantBuffer = nullptr;
	};
}

