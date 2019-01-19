#pragma once
#include "../Data/math_structs.h"
#include "utils.h"

struct Vertex
{
	float3 position;
	float3 normal;
	float3 uv;

	Vertex() : position({}), normal (UNIDENTIFIED_NORMAL), uv({}) {}
	explicit Vertex (const float3& position) : position(position), normal(UNIDENTIFIED_NORMAL), uv({}) {}
};
