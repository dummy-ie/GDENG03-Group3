#include "Mesh.h"

#include <filesystem>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "GraphicsEngine.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "VertexMesh.h"


Mesh::Mesh(const wchar_t* fullPath, const std::string& name) : Resource(fullPath), GameObject(name)
{
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::string inputFile = std::filesystem::path(fullPath).string();

	LogUtils::logBool(
		this,
		tinyobj::LoadObj(&attributes, &shapes, &materials, &warn, &err, inputFile.c_str())
	);

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

	std::vector<VertexMesh> listVertices;
	std::vector<unsigned int> listIndices;


	for (auto& [name, mesh, lines, points] : shapes)
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

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
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

const VertexBufferPtr& Mesh::getVertexBuffer()
{
	return vertexBuffer;
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
	return indexBuffer;
}
