#include "Triangle.h"
#include <cassert>

float3 Triangle::getColor() const
{
	auto t = (float)1 / 3;
	return getColor(t, t, t);
}

float3 Triangle::getColor(float l1, float l2, float l3) const
{
	return l1 * c1 + l2 * c2 + l3 * c3;
}

float Triangle::getDepth() const
{
	const auto t = (float)1 / 3;
	return getDepth(t, t, t);
}

float Triangle::getDepth(float l1, float l2, float l3) const
{
	return l1 * p1.z + l2 * p2.z + l3 * p3.z;
}

int Triangle::checkBarycentric(float l1, float l2, float l3) const
{
	return l1 + l2 + l3 == 1 ? 0 : -1;
}

void Triangle::calculateNormals()
{
//	auto u = p2 - p1;
//	auto v = p3 - p1;
//	auto n = cross(u, v);
//
//	n1 = n2 = n3 = normalize(n);
}

float3 Triangle::getNormal() const
{
	auto t = 1.f / 3;
	return getNormal(t, t, t);
}

float3 Triangle::getNormal(float l1, float l2, float l3) const
{
//	return l1 * n1 + l2 * n2 + l3 * n3;
	if (areNormalsInitialized()) {
		return l1 * n1 + l2 * n2 + l3 * n3;
	}

	auto u = p2 - p1;
	auto v = p3 - p1;
	auto n = cross(u, v);

	return normalize(n);
}

float3 Triangle::getPosition() const
{
	auto t = 1.f / 3;
	return getPosition(t, t, t);
}

float3 Triangle::getPosition(float l1, float l2, float l3) const
{
	return l1 * p1 + l2 * p2 + l3 * p3;
}

float3 Triangle::getUV() const
{
    auto t = 1.f / 3;
    return getUV(t, t, t);
}

float3 Triangle::getUV(float l1, float l2, float l3) const
{
	return l1 * uv1 + l2 * uv2 + l3 * uv3;
}

bool Triangle::areNormalsInitialized() const
{
	return !isEqual(n1, UNIDENTIFIED_NORMAL) &&
	       !isEqual(n2, UNIDENTIFIED_NORMAL) &&
	       !isEqual(n3, UNIDENTIFIED_NORMAL);

}
