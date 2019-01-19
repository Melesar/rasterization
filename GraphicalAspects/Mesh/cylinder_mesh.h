#pragma once
#include "mesh.h"

class CylinderMesh : public Mesh
{
	const float3 center;
	const float radius;
	const int verticalSegments;
	const int horizontalSegments;

	const float angleStep;
	const float3 centerTop;

	const float segmentLength;

public:

	CylinderMesh(const float3& center, float radius, int verticalSegments, int horizontalSegments);

private:

	void makeVertices();
	void makeIndices();
};
