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
	~ObjParser();
	ObjParser();

private:

	const int InvalidValue = -13;

	float3 getVertex(std::istream& stream);
	float3 getUV(std::istream& stream);
	float3 getNormal(std::istream& stream);
	Vertex getVertex (std::istream& stream, const std::vector<float3>& verticies, const std::vector<float3>& uvs, const std::vector<float3>& normals);
	void parseFace(std::stringstream& stream, std::vector<Triangle>& triangles, const std::vector<float3>& verticies, const std::vector<float3>& uvs, const std::vector<float3>& normals);

	std::ofstream* fDebug;
};
