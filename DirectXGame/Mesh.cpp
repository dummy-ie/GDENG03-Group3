#include "Mesh.h"

#include <filesystem>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "GraphicsEngine.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "VertexMesh.h"


namespace gdeng03
{
	Mesh::Mesh(const wchar_t* fullPath) : Resource(fullPath), primitiveType(PrimitiveType::NOT_PRIMITIVE)
	{
		tinyobj::attrib_t attributes;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		std::string inputFile = std::filesystem::path(fullPath).string();

		LogUtils::logBool(
			this,
			tinyobj::LoadObj(&attributes, &shapes, &materials, &warn, &err, inputFile.c_str()),
			false
		);

		if (!err.empty()) throw std::exception(std::string("Mesh not created successfully: " + err).c_str());

		if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

		std::vector<VertexMesh> listVertices;
		std::vector<unsigned int> listIndices;


		for (auto& [shapeName, mesh, lines, points] : shapes)
		{
			size_t indexOffset = 0;
			int vectorSize = 0;
			for (size_t s = shapes.size(); s-- > 0; ) {
				vectorSize += mesh.indices.size();
			}
			listVertices.reserve(vectorSize);
			listIndices.reserve(vectorSize);
			// listVertices.reserve(mesh.indices.size());
			// listIndices.reserve(mesh.indices.size());

			for (size_t f = 0; f < mesh.num_face_vertices.size(); f++)
			{
				unsigned char numFaceVertices = mesh.num_face_vertices[f];

				for (unsigned char v = 0; v < numFaceVertices; v++)
				{
					auto [vertexIndex, normalIndex, texcoordIndex] = mesh.indices[indexOffset + v];

					tinyobj::real_t vx = attributes.vertices[vertexIndex * 3 + 0];
					tinyobj::real_t vy = attributes.vertices[vertexIndex * 3 + 1];
					tinyobj::real_t vz = attributes.vertices[vertexIndex * 3 + 2];

					tinyobj::real_t tx = 0;
					tinyobj::real_t ty = 0;

					if (texcoordIndex >= 0 && !attributes.texcoords.empty())
					{
						tx = attributes.texcoords[texcoordIndex * 2 + 0];
						ty = attributes.texcoords[texcoordIndex * 2 + 1];
					}

					VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty), Vector3D(1, 1, 1));
					listVertices.push_back(vertex);

					listIndices.push_back(static_cast<unsigned int>(indexOffset) + v);
				}

				indexOffset += numFaceVertices;
			}
		}

		void* shaderByteCode = nullptr;
		size_t sizeShader = 0;
		GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shaderByteCode, &sizeShader);
		vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(listVertices.data(), sizeof(VertexMesh),
			static_cast<UINT>(listVertices.size()), shaderByteCode, static_cast<UINT>(sizeShader));
		indexBuffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(listIndices.data(), static_cast<UINT>(listIndices.size()));

		Constant constants;

		constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&constants, sizeof(Constant));
	}

	Mesh::Mesh(const PrimitiveType type) : Resource(toString(type)), primitiveType(type)
	{
		std::vector<VertexMesh> listVertices;
		std::vector<unsigned int> listIndices;

		switch (type)
		{
		case PrimitiveType::CUBE:
			createCubeMesh(listVertices, listIndices);
			break;
		case PrimitiveType::PLANE:
			createPlaneMesh(listVertices, listIndices);
			break;
		case PrimitiveType::SPHERE:
			createSphereMesh(listVertices, listIndices);
			break;
		case PrimitiveType::CAPSULE:
			createCapsuleMesh(listVertices, listIndices);
			break;
		case PrimitiveType::NOT_PRIMITIVE:
			LogUtils::error(this, "Do not load a NOT_PRIMITIVE mesh!");
			return;
		}

		void* shaderByteCode = nullptr;
		size_t sizeShader = 0;
		GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shaderByteCode, &sizeShader);
		vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(listVertices.data(), sizeof(VertexMesh),
			static_cast<UINT>(listVertices.size()), shaderByteCode, static_cast<UINT>(sizeShader));
		indexBuffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(listIndices.data(), static_cast<UINT>(listIndices.size()));

		Constant constants;

		constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&constants, sizeof(Constant));
	}

	PrimitiveType Mesh::getType() const
	{
		return primitiveType;
	}

	void Mesh::createCubeMesh(std::vector<VertexMesh>& listVertices, std::vector<unsigned int>& listIndices)
	{
			//FRONT FACE
		listVertices.push_back(VertexMesh(Vector3D(-0.5f, -0.5f, -0.5f), Vector2D(0, 1)));
		listVertices.push_back(VertexMesh(Vector3D(-0.5f, 0.5f, -0.5f), Vector2D(0, 0)));
		listVertices.push_back(VertexMesh(Vector3D(0.5f, 0.5f, -0.5f), Vector2D(1, 0)));
		listVertices.push_back(VertexMesh(Vector3D(0.5f, -0.5f, -0.5f), Vector2D(1, 1)));

		listVertices.push_back(VertexMesh(Vector3D(0.5f, 0.5f, -0.5f), Vector2D(1, 1)));
		listVertices.push_back(VertexMesh(Vector3D(0.5f, 0.5f, 0.5f), Vector2D(1, 0)));
		listVertices.push_back(VertexMesh(Vector3D(-0.5f, 0.5f, 0.5f), Vector2D(0, 0)));
		listVertices.push_back(VertexMesh(Vector3D(-0.5f, 0.5f, -0.5f), Vector2D(0, 1)));

		listVertices.push_back(VertexMesh(Vector3D(0.5f, -0.5f, 0.5f), Vector2D(0, 1)));
		listVertices.push_back(VertexMesh(Vector3D(0.5f, 0.5f, 0.5f), Vector2D(0, 0)));
		listVertices.push_back(VertexMesh(Vector3D(-0.5f, 0.5f, 0.5f), Vector2D(1, 0)));
		listVertices.push_back(VertexMesh(Vector3D(-0.5f, -0.5f, 0.5f), Vector2D(1, 1)));

		listVertices.push_back(VertexMesh(Vector3D(0.5f, -0.5f, -0.5f), Vector2D(0, 1)));
		listVertices.push_back(VertexMesh(Vector3D(0.5f, -0.5f, 0.5f), Vector2D(0, 0)));
		listVertices.push_back(VertexMesh(Vector3D(-0.5f, -0.5f, 0.5f), Vector2D(1, 0)));
		listVertices.push_back(VertexMesh(Vector3D(-0.5f, -0.5f, -0.5f), Vector2D(1, 1)));


		unsigned int indexList[] = {

			//FRONT SIDE
			0,1,2,  //FIRST TRIANGLE
			2,3,0,  //SECOND TRIANGLE
			//TOP SIDE
			4,7,6,
			6,5,4,
			//BACK SIDE
			8,9,10,
			10,11,8,
			//BOTTOM SIDE
			12,13,14,
			14,15,12,
			//RIGHT SIDE
			2,9,8,
			8,3,2,
			//LEFT SIDE
			1,0,11,
			11,10,1

		};

		for  (unsigned int index : indexList)
		{
			listIndices.push_back(index);
		}
	}

	void Mesh::createPlaneMesh(std::vector<VertexMesh>& listVertices, std::vector<unsigned int>& listIndices)
	{ 
		
		listVertices.push_back(VertexMesh( Vector3D(-.5f, 0, -.5f),  Vector2D(0, 1)));
		listVertices.push_back(VertexMesh( Vector3D(-.5f, 0, .5f), Vector2D(0, 0) ));
		listVertices.push_back(VertexMesh( Vector3D(.5f, 0, .5f), Vector2D(1, 0) ));
		listVertices.push_back(VertexMesh( Vector3D(.5f, 0, -.5f), Vector2D(1, 1) ));

		listVertices.push_back(VertexMesh( Vector3D(.5f, 0, -.5f), Vector2D(0, 1) ));
		listVertices.push_back(VertexMesh( Vector3D(.5f, 0, .5f), Vector2D(0, 0) ));
		listVertices.push_back(VertexMesh( Vector3D(-.5f, 0, .5f), Vector2D(1, 0) ));
		listVertices.push_back(VertexMesh( Vector3D(-.5f, 0, -.5f), Vector2D(1, 1)));

		unsigned int indexList[] = {

		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		////BACK SIDE
		4,5,6,
		6,7,4,
		};

		for (unsigned int index : indexList)
		{
			listIndices.push_back(index);
		}
	}

	void Mesh::createSphereMesh(std::vector<VertexMesh>& listVertices, std::vector<unsigned int>& listIndices)
	{
		constexpr int segments = 50;
		for (int i = 0; i <= segments; i++) {
			constexpr float radius = 1.f;
			const float phi = M_PI * i * 2.f / segments;
			const float y = radius * cosf(phi);
			const float r = radius * sinf(phi);

			for (int j = 0; j <= segments; j++) {
				const float theta = M_PI * j * 2.f / segments;
				const float x = r * cosf(theta);
				const float z = r * sinf(theta);

				//Vector3D normal = Vector3D(x / radius, y / radius, z / radius);

				listVertices.push_back({ Vector3D(x, y, z), Vector2D(theta, phi) });


				const int current = i * (segments + 1) + j;
				const int next = current + segments + 1;

				listIndices.push_back(current);
				listIndices.push_back(next);
				listIndices.push_back(current + 1);

				listIndices.push_back(current + 1);
				listIndices.push_back(next);
				listIndices.push_back(next + 1);
			}
		}
	}

	void Mesh::createCapsuleMesh(std::vector<VertexMesh>& listVertices, std::vector<unsigned int>& listIndices)
	{
		constexpr int segments = 50;
		constexpr float radius = .5f;
		for (int i = 0; i <= segments / 2; i++) {
			const float phi = M_PI * 2.f * i / segments / 2;
			const float y = radius * cosf(phi) + .5f;
			const float r = radius * sinf(phi);

			for (int j = 0; j <= segments; j++) {
				const float theta = M_PI * 2.f * j / segments;
				listVertices.push_back({ Vector3D(r * sinf(theta), y, r * cosf(theta)), Vector2D(theta, phi) });
				if (i == segments) listVertices.push_back({ Vector3D(r * sinf(theta), y,r * cosf(theta)),  Vector2D(theta, .5f) });

				const int current = i * (segments + 1) + j;
				const int next = current + segments + 1;

				listIndices.push_back(current);
				listIndices.push_back(next);
				listIndices.push_back(current + 1);

				listIndices.push_back(current + 1);
				listIndices.push_back(next);
				listIndices.push_back(next + 1);
			}
		}

		for (int i = 0; i <= 1; i++) {
			const float y = (i == 0) ? .5f : -.5f;

			for (int j = 0; j <= segments; j++) {
				const float theta = M_PI * 2.f * j / segments;

				listVertices.push_back({ Vector3D(radius * sinf(theta), y, radius * cosf(theta)),  Vector2D(theta,0.5f + y) });

				const int current = i * (segments + 1) + j;
				const int next = current + segments + 1;

				listIndices.push_back(current + 1);
				listIndices.push_back(next);
				listIndices.push_back(next + 1);

				listIndices.push_back(current);
				listIndices.push_back(next);
				listIndices.push_back(current + 1);

			}
		}

		for (int i = 0; i <= segments + 2; i++) {
			const float phi = M_PI * 2.f * i / segments / 2;
			const float y = radius * cosf(phi) - .5f;
			const float r = radius * sinf(phi);

			if (i > (segments / 2) - 1) {
				for (int j = 0; j <= segments; j++) {
					const float theta = M_PI * 2.f * j / segments;
					listVertices.push_back({ Vector3D(r * sinf(theta), y,r * cosf(theta)), Vector2D(theta, phi) });

					const int current = i * (segments + 1) + j;
					const int next = current + segments + 1;

					listIndices.push_back(current + 1);
					listIndices.push_back(next);
					listIndices.push_back(next + 1);

					listIndices.push_back(current);
					listIndices.push_back(next);
					listIndices.push_back(current + 1);


				}
			}
		}
	}

	const VertexBufferPtr& Mesh::getVertexBuffer()
	{
		return vertexBuffer;
	}

	const IndexBufferPtr& Mesh::getIndexBuffer()
	{
		return indexBuffer;
	}
}
