#include "objParser.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <file_utils.h>
#include <cstring>

namespace optimization
{
	void ObjParser::parse(const std::string & fileName, std::vector<Triangle>& triangles)
	{
		FILE* f = fopen(fileName.c_str(), "r");

		std::vector<float3> verticies, uvs, normals;
		char line [LINE_LENGTH];

		while (readLine(f, line))
		{
			char token[3];
			char content[LINE_LENGTH - 3];
			getToken(line, token, content);
			float3 v;
			if (strcmp(token, "v") == 0) {
				getFloat3(content, v);
				verticies.push_back(v);
			} else if (strcmp(token, "vt") == 0) {
				getFloat3(content, v);
				uvs.push_back(v);
			} else if (strcmp(token, "vn") == 0) {
				getFloat3(content, v);
				normals.push_back(v);
			} else if (strcmp(token, "f") == 0) {
				parseFace(content, triangles, verticies, uvs, normals);
			}
		}

		fclose(f);
	}


	void ObjParser::parseFace(char* content, std::vector<Triangle>& triangles, const std::vector<float3>& verticies, const std::vector<float3>& uvs, const std::vector<float3>& normals)
	{
		try {
			Vertex faceVertices[4];
			int verticesParsed = 0;
			VertexData v;
			while (getVertex(content, v)) {
				Vertex vert;
				vert.position = verticies[v.posIndex];
				if (v.uvIndex > 0) {
					vert.uv = uvs[v.uvIndex];
				}
				if (v.normalIndex > 0) {
					vert.normal = normals[v.normalIndex];
				}

				faceVertices[verticesParsed++] = vert;
			}

			if (verticesParsed < 3) {
				throw InvalidValue;
			}

			int trisCount = verticesParsed - 2;
			for (size_t i = 0; i < trisCount; i++) {
				Triangle t;
				t.v1 = faceVertices[0];
				t.v2 = faceVertices[i + 1];
				t.v3 = faceVertices[i + 2];

				triangles.push_back(t);
			}
		}
		catch (const int& err) {
			if (err == InvalidValue) {
				std::cout << "Failed to parse face " << content << std::endl;
			}
		}
	}
}


