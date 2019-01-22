#include "cylinder_mesh.h"
#include <cmath>

CylinderMesh::CylinderMesh(const float3& center, float radius, int verticalSegments, int horizontalSegments):
	center(center),
	radius(radius),
	verticalSegments(verticalSegments),
	horizontalSegments(horizontalSegments),
	angleStep(360.f / horizontalSegments),
	centerTop(center + float3{ 0, verticalSegments * segmentLength, 0 }),
	segmentLength(0.5f)
{
	makeVertices();
	makeIndices();
	//calculateNormals();
}

void CylinderMesh::makeVertices()
{
	const auto centerBottom = float3 {0, 0, 0};
	const auto centerTop = centerBottom + float3{ 0, verticalSegments * segmentLength, 0 };

	vertices.emplace_back(centerBottom);

	for (int i = 0; i <= verticalSegments; ++i)
	{
		for (int j = 0; j < horizontalSegments; ++j)
		{
			auto rad = (j * angleStep) * PI / 180.f;
			auto c = cos(rad);
			auto s = sin(rad);
			float x = c * radius;
			float y = i * segmentLength;
			float z = s * radius;

			vertices.emplace_back(centerBottom + float3{ x, y, z });
		}
	}

	vertices.emplace_back(centerTop);
}

void CylinderMesh::makeIndices()
{
	for (int i = 0; i < verticalSegments; ++i)
	{
		for(int j = 0; j < horizontalSegments; j++)
		{
			auto current = i * horizontalSegments + j + 1;
			auto next = current + horizontalSegments;

			indices.emplace_back(int3{current, current + 1, next});
			indices.emplace_back(int3{current + 1, next + 1, next});
		}
	}

	for(int i = 0; i < horizontalSegments; i++)
	{
		auto bottom = i + 1;
		auto top = bottom + verticalSegments * horizontalSegments;

		int3 tris {top, top + 1, (int) vertices.size() - 1};
		indices.emplace_back(tris);
		vertices[tris.a].normal = float3{0, 1, 0};
		vertices[tris.b].normal = float3{0, 1, 0};
		vertices[tris.c].normal = float3{0, 1, 0};
	}
}