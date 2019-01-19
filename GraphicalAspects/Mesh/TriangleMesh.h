#pragma once
#include "mesh.h"

struct float3;

class TriangleMesh : public Mesh
{
public:
	TriangleMesh(const float3& v1, const float3& v2, const float3& v3);
	TriangleMesh(const Triangle& t);
};
