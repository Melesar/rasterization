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
	calculateNormals();
}

void CylinderMesh::makeVertices()
{
	const auto centerBottom = float3 {0, 0, 0};
	const auto centerTop = center + float3{ 0, verticalSegments * segmentLength, 0 };

	vertices.emplace_back(centerBottom);

	for (int i = 0; i <= verticalSegments; ++i)
	{
		for (int j = 0; j < horizontalSegments; ++j)
		{
			auto c = cos(j * angleStep);
			auto s = sin(j * angleStep);
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
	for (int i = 0; i < horizontalSegments - 1; ++i)
	{
		indices.emplace_back(int3{ 0, i + 1, i + 2 });
		for (int j = 0; j < verticalSegments; ++j)
		{
			auto cur = j * horizontalSegments;
			auto next = (j + 1) * horizontalSegments;

			indices.emplace_back(int3{cur + i + 1, next + i + 1, cur + i + 2});
			indices.emplace_back(int3{next + i + 1, next + i + 2, cur + i + 2});
		}

		auto ii = verticalSegments  * horizontalSegments + i;
		indices.emplace_back(int3{ ii + 1, int(vertices.size()) - 1, ii + 2 });
	}
}