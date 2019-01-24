#pragma once

#include <string>
#include <vector>
#include <map>
#include "../Data/Triangle.h"
#include "../Mesh/vertex.h"


class ObjParser
{
public:

	void parse(const std::string& fileName, std::vector<Triangle>& triangles);
	~ObjParser() = default;

private:

	const int InvalidValue = -13;

	void parseFace(char* content, std::vector<Triangle>& triangles, const std::vector<float3>& verticies, const std::vector<float3>& uvs, const std::vector<float3>& normals);
};
