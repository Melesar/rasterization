#pragma once
#include "../Rasterizer/Rasterizer.h"
#include "../VertexProcessor/VertexProcessor.h"
#include "vertex.h"
#include <vector>

class Mesh
{
public:

	void draw(const Rasterizer& r, VertexProcessor& vp) const;

	void setVertices(const std::vector<Vertex>& vertices);
	void setIndices(const std::vector<int3>& indices);
	void setColor(const float3& color);
	void setColors(float3* triangleColors);

	void setTexture(class Texture* texture);

	Mesh();
	virtual ~Mesh();

	static Mesh* create(const std::string& fileName);

protected:

	std::vector<Vertex> vertices;
	std::vector<int3> indices;

	float3* color;
	bool isTriangleColors;

	Texture* texture;

	void calculateNormals();
};
