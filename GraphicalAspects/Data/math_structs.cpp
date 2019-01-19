#include "math_structs.h"
#include <complex>

float& float3::operator[](int index) const
{
	return *const_cast<float*>(&x + index);
}

float3 float3::operator*(float v) const
{
	return { x * v, y * v, z * v };
}

float3 float3::operator+(float3 v) const
{
	return { v.x + x, v.y + y, v.z + z };
}

float3 float3::operator-(float3 v) const
{
	return { x - v.x, y - v.y, z - v.z };
}

float3 float3::operator-() const
{
	return { -x, -y, -z };
}

float4::float4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float4::float4(const float3 v, float w) : float4(v.x, v.y, v.z, w)
{
}

float& float4::operator[](int index) const
{
	return *const_cast<float*>(&x + index);
}

float4 float4::operator*(float v) const
{
	return { x * v, y * v, z * v, w * v };
}

float4 float4::operator+(float4 v) const
{
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

float4& float4x4::operator[](int index) const
{	
	return *const_cast<float4*>(columns + index);
}

float4x4::float4x4(const float4 a, const float4 b, const float4 c, const float4 d)
{
	columns[0] = a;
	columns[1] = b;
	columns[2] = c;
	columns[3] = d;
}

float dot(float3 a, float3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float dot(float4 a, float4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float3 cross(float3 a, float3 b)
{
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

float3 mul(float3 v, const float4x4& m, bool isHomogenuous)
{
	const float4 v4 = { v, isHomogenuous ? 1.f : 0.f };
	const auto res = mul(v4, m);

	return !isEqual(res.w, 0.f) && !isEqual(res.w, 1.f)
			? float3 { res.x / res.w, res.y / res.w, res.z / res.w }
			: float3 {res.x, res.y, res.z};
}

float4 mul(float4 v, const float4x4& m)
{
	auto r = transpose(m);
	return {
		dot(v, r[0]),
		dot(v, r[1]),
		dot(v, r[2]),
		dot(v, r[3]),
	};
}

float4x4 mul(const float4x4& a, const float4x4& b)
{
	auto l = transpose(a);
	return {
		{dot(l[0], b[0]), dot(l[1], b[0]), dot(l[2], b[0]), dot(l[3], b[0]) },
		{dot(l[0], b[1]), dot(l[1], b[1]), dot(l[2], b[1]), dot(l[3], b[1]) },
		{dot(l[0], b[2]), dot(l[1], b[2]), dot(l[2], b[2]), dot(l[3], b[2]) },
		{dot(l[0], b[3]), dot(l[1], b[3]), dot(l[2], b[3]), dot(l[3], b[3]) },
	};
}

float len(const float3 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float len(const float4 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float3 normalize(const float3 v)
{
	auto l = len(v);
	if (l <= 0.0001f)
	{
		return v;
	}

	return { v.x / l, v.y / l, v.z / l };
}

float4 normalize(const float4 v)
{
	auto l = len(v);
	if (l <= 0.0001f) 
	{
		return v;
	}

	return { v.x / l, v.y / l, v.z / l, v.z / l};
}

float4x4 transpose(const float4x4& m)
{
	float4x4 res;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j) 
		{
			res[i][j] = m[j][i];
		}
	}

	return res;
}

float3 operator*(float v, float3 vec)
{
	return vec * v;
}

std::ostream& operator<<(std::ostream& s, float3 v)
{
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return s;
}

float4 operator*(float v, float4 vec)
{
	return vec * v;
}

bool isEqual(float a, float b, float eps)
{
	return std::abs(a - b) < eps;
}

bool isEqual(float3 a, float3 b, float eps)
{
    return isEqual(a.x, b.x, eps) &&
     		isEqual(a.y, b.y, eps) &&
     		isEqual(a.z, b.z, eps);
}
