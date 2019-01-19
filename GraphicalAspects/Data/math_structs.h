#pragma once
#include <ostream>

struct float3
{
	union
	{
		struct { float x, y, z; };
		struct { float r, g, b; };
	};

	float& operator [] (int index) const;
	float3 operator * (float v) const;
	friend float3 operator * (float v, float3 vec);
	float3 operator + (float3 v) const;
	float3 operator - (float3 v) const;
	float3 operator - () const;

	friend std::ostream& operator << (std::ostream& s, float3 v);
};

struct float4
{
	float x, y, z, w;

	float4() = default;
	float4(float x, float y, float z, float w);
	float4(const float3 v, float w);

	float& operator [] (int index) const;
	float4 operator * (float v) const;
	friend float4 operator * (float v, float4 vec);
	float4 operator + (float4 v) const;
};

struct float4x4
{
	float4 columns[4];

	float4& operator[] (int index) const;

	float4x4() = default;
	float4x4(float4 a, float4 b, float4 c, float4 d);
};

struct int3
{
	int a, b, c;
};

float dot(float3 a, float3 b);
float dot(float4 a, float4 b);

float3 cross(float3 a, float3 b);

float3 mul(float3 v, const float4x4& m, bool isHomogenuous = true);
float4 mul(float4 v, const float4x4& m);
float4x4 mul(const float4x4& a, const float4x4& b);

float len(const float3 v);
float len(const float4 v);

float3 normalize(const float3 v);
float4 normalize(const float4 v);

float4x4 transpose(const float4x4& m);

bool isEqual(float a, float b, float eps = 0.001f);
bool isEqual(float3 a, float3 b, float eps = 0.001f);
