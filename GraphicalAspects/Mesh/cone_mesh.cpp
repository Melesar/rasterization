#include <cmath>
#include "cone_mesh.h"
#include <cmath>

ConeMesh::ConeMesh(float radius, float height, int resolution)
	: radius(radius), height(height), resolution(resolution)
{
	makeVertices();
	makeIndices();
	calculateNormals();
}

void ConeMesh::makeVertices()
{
	vertices.emplace_back(float3{0, 0, 0});

	const float angleStep = (360.f / resolution) * PI / 180.f;
	for (int i = 0; i < resolution; ++i)
	{
		auto x = cos(i * angleStep) * radius;
		auto z = sin(i * angleStep) * radius;

		vertices.emplace_back(float3{ x, 0, z });
	}

	vertices.emplace_back(float3{ 0, height, 0 });
}

void ConeMesh::makeIndices()
{
	const int iTop = vertices.size() - 1;
    for (int i = 1; i <= resolution; ++i)
	{
		auto next = i + 1 <= resolution ? i + 1 : i + 1 - resolution;
		indices.emplace_back(int3{ next, iTop, i   });
		indices.emplace_back(int3{ 0, next, i });
	}
}


