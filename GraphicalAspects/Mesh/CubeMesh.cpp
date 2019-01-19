#include "CubeMesh.h"
#include <cassert>

CubeMesh::CubeMesh(const float3& extents)
	: extents(extents)
{
	assert(extents.x > 0 && extents.y > 0 && extents.z > 0);

	buildFace(float3{ 0, extents.y, 0 });
	buildFace(float3{ 0, -extents.y, 0 });

	indices.emplace_back(int3{ 1, 4, 5 });
	indices.emplace_back(int3{ 1, 0, 4 });
	indices.emplace_back(int3{ 1, 5, 6 });
	indices.emplace_back(int3{ 1, 5, 6 });
	indices.emplace_back(int3{ 6, 2, 1 });
	indices.emplace_back(int3{ 3, 2, 6 });
	indices.emplace_back(int3{ 6, 7, 3 });
	indices.emplace_back(int3{ 6, 7, 3 });
	indices.emplace_back(int3{ 0, 3, 7 });
	indices.emplace_back(int3{ 7, 4, 0 });
	indices.emplace_back(int3{ 2, 0, 1 });
	indices.emplace_back(int3{ 2, 3, 0 });
	indices.emplace_back(int3{ 6, 5, 4 });
	indices.emplace_back(int3{ 4, 7, 6 });

	calculateNormals();
}

float3 CubeMesh::getSize() const
{
	return 2 * extents;
}

void CubeMesh::buildFace(const float3& origin)
{
	vertices.emplace_back(origin + float3{ extents.x, 0, extents.z });
	vertices.emplace_back(origin + float3{ -extents.x, 0, extents.z });
	vertices.emplace_back(origin + float3{ -extents.x, 0, -extents.z });
	vertices.emplace_back(origin + float3{ extents.x, 0, -extents.z });
}
