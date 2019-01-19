#include "VertexProcessor.h"
#include "../utils.h"

Triangle VertexProcessor::triangleToProjection(const Triangle &tr)
{
	auto t (tr);

	t.p1 = mul(t.p1, objectToProjection);
	t.p2 = mul(t.p2, objectToProjection);
	t.p3 = mul(t.p3, objectToProjection);

	t.n1 = normalize(mul(t.n1, objToView, false));
	t.n2 = normalize(mul(t.n2, objToView, false));
	t.n3 = normalize(mul(t.n3, objToView, false));

	return t;
}

Triangle VertexProcessor::triangleToView(const Triangle &tr)
{
    auto t (tr);

    t.p1 = mul(t.p1, objToView);
    t.p2 = mul(t.p2, objToView);
    t.p3 = mul(t.p3, objToView);

    t.n1 = normalize(mul(t.n1, objToView, false));
    t.n2 = normalize(mul(t.n2, objToView, false));
    t.n3 = normalize(mul(t.n3, objToView, false));

    return t;
}

void VertexProcessor::lt()
{
}

void VertexProcessor::setPerspective(float fovy, float aspect, float znear, float zfar)
{
	fovy = fovy * PI / 360.f;
	float f = cos(fovy) / sin(fovy);

	viewToProj[0] = { f / aspect, 0, 0, 0 };
	viewToProj[1] = { 0, f, 0, 0 };
	viewToProj[2] = { 0, 0, (zfar + znear) / (znear - zfar), -1 };
	viewToProj[3] = { 0, 0, 2 * zfar * znear / (znear - zfar), 0 };

	recalculateTransformMatrix();
}

void VertexProcessor::setLookat(const float3& center, const float3& eye, const float3& up)
{
	auto f = center - eye;
	viewDirection = normalize(f);
	auto nup = normalize(up);
	auto s = cross(viewDirection, nup);
	auto u = cross(s, viewDirection);

	worldToView[0] = { s[0], u[0], -viewDirection[0], 0 };
	worldToView[1] = { s[1], u[1], -viewDirection[1], 0 };
	worldToView[2] = { s[2], u[2], -viewDirection[2], 0 };
	worldToView[3] = { -eye, 1 };

	recalculateTransformMatrix();
}

void VertexProcessor::multByTranslation(const float3& v)
{
	float4x4 m = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{v.x, v.y, v.z, 1}
	};

	objToWorld = mul(m, objToWorld);
	recalculateTransformMatrix();
}

void VertexProcessor::multByRotation(const float3& v, float angle)
{
	auto s = sin(angle * PI / 180);
	auto c = cos(angle * PI / 180);
	auto r = normalize(v);

	float4x4 m = {
		{ r.x * r.x * (1 - c) + c, r.y * r.x * (1 - c) + r.z * s, r.x * r.z * (1 - c) - r.y * s, 0 },
		{ r.x * r.y * (1 - c) - r.z * s, r.y * r.y * (1 - c) + c, r.y * r.z * (1 - c) + r.x * s, 0 },
		{ r.x * r.z * (1 - c) + r.y * s, r.y * r.z * (1 - c) - r.x * s, r.z * r.z * (1 - c) + c, 0 },
		{0, 0, 0, 1}
	};

	objToWorld = mul(m, objToWorld);
	recalculateTransformMatrix();
}

void VertexProcessor::multByScale(const float3& v)
{
	float4x4 m = {
		{v.x, 0, 0, 0},
		{0, v.y, 0, 0},
		{0, 0, v.z, 0},
		{0, 0, 0, 1}
	};

	objToWorld = mul(m, objToWorld);
	recalculateTransformMatrix();
}

VertexProcessor::VertexProcessor()
{
	identity = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	objToWorld = identity;
	viewToProj = identity;
	worldToView = identity;
}

void VertexProcessor::recalculateTransformMatrix()
{
	objToView = mul(worldToView, objToWorld);
	objectToProjection = mul(viewToProj, objToView);
}

void VertexProcessor::setIdentity()
{
	objToWorld = identity;
	recalculateTransformMatrix();
}

float3 VertexProcessor::obj2World(const float3 &v) const
{
	return mul(v, objToWorld);
}

float3 VertexProcessor::world2View(const float3 &v, bool isDirection) const
{
	return mul(v, worldToView, !isDirection);
}

float3 VertexProcessor::getViewDirection() const
{
    return viewDirection;
}
