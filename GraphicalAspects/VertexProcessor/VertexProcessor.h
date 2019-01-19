#pragma once
#include "../Data/math_structs.h"
#include "../Data/Triangle.h"

class VertexProcessor
{
public:

	Triangle triangleToProjection(const Triangle &tr);
	Triangle triangleToView(const Triangle &tr);

	float3 obj2World(const float3& v) const;
	float3 world2View(const float3& v, bool isDirection = false) const;

	float3 getViewDirection() const;

	void lt();

	void setPerspective(float fovy, float aspect, float znear, float zfar);
	void setLookat(const float3& center, const float3& eye, const float3& up);

	void multByTranslation(const float3& v);
	void multByRotation(const float3& v, float angle);
	void multByScale(const float3& v);

	void setIdentity();

	VertexProcessor();

private:

	float4x4 objToWorld;
	float4x4 worldToView;
	float4x4 viewToProj;

	float4x4 objToView;
	float4x4 objectToProjection;

	float4x4 identity;

	float3 viewDirection;

	void recalculateTransformMatrix();
};
