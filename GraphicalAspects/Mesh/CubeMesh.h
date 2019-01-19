#pragma once
#include "mesh.h"

class CubeMesh : public Mesh
{
private:
	float3 extents;

public:
	CubeMesh(const float3& extents);

	float3 getSize() const;

private:

	void buildFace(const float3& origin);
};
