#pragma once
#include <algorithm>
#include <Mesh/vertex.h>
#include "math_structs.h"

struct Triangle
{
    union
    {
        Vertex v1;
        struct {float3 p1; float3 n1; float3 uv1;};
    };

    union
    {
        Vertex v2;
        struct {float3 p2; float3 n2; float3 uv2;};
    };

    union
    {
        Vertex v3;
        struct {float3 p3; float3 n3; float3 uv3;};
    };

	float3 c1, c2, c3;

	float maxX() const { return std::max(std::max(p1.x, p2.x), p3.x); }
	float maxY() const { return std::max(std::max(p1.y, p2.y), p3.y); }
	float minX() const { return std::min(std::min(p1.x, p2.x), p3.x); }
	float minY() const { return std::min(std::min(p1.y, p2.y), p3.y); }

	float3 getColor() const;
	float3 getColor(float l1, float l2, float l3) const;

	float getDepth() const;
	float getDepth(float l1, float l2, float l3) const;

	float3 getNormal() const;
	float3 getNormal(float l1, float l2, float l3) const;

    float3 getPosition() const;
    float3 getPosition(float l1, float l2, float l3) const;

	float3 getUV() const;
	float3 getUV(float l1, float l2, float l3) const;

	void calculateNormals();


	Triangle() {}

	Triangle (const Vertex& v1, const Vertex& v2, const Vertex& v3, const float3& color = {1, 1, 1})
	    : v1(v1), v2(v2), v3(v3), c1(color), c2 (color), c3(color)
    {}

	Triangle(const float3& v1, const float3& v2, const float3& v3, const float3& color = { 1, 1, 1 })
		: p1(v1), p2(v2), p3(v3), c1(color), c2(color), c3(color)
	{
	}

	Triangle(const float3& v1, const float3& v2, const float3& v3,
			 const float3& c1, const float3& c2, const float3& c3)
		:p1(v1), p2(v2), p3(v3), c1(c1), c2(c2), c3(c3)
	{ }

private:
	int checkBarycentric(float l1, float l2, float l3) const;
	bool areNormalsInitialized() const;
};
