#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(const float3& v1, const float3& v2, const float3& v3)
{
	vertices.emplace_back(v1);
	vertices.emplace_back(v2);
	vertices.emplace_back(v3);

	indices.emplace_back(int3{ 0, 1, 2 });
}

TriangleMesh::TriangleMesh(const Triangle& t) :
	TriangleMesh(t.p1, t.p2, t.p3)
{

}
