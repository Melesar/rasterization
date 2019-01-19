#include "mesh.h"
#include "Texture/texture.h"
#include "../Parser/objParser.h"
#include <iostream>

void Mesh::draw(const Rasterizer& r, VertexProcessor& vp) const
{
	for (auto index : indices)
	{
		auto t = Triangle {
			vertices[index.a],
			vertices[index.b],
			vertices[index.c],
		};

		if (isTriangleColors)
		{
			t.c1 = color[0];
			t.c2 = color[1];
			t.c3 = color[2];
		}
		else
		{
			t.c1 = t.c2 = t.c3 = *color;
		}

		r.triangle(t, vp, texture);
	}
}

void Mesh::setVertices(const std::vector<Vertex>& vertices)
{
	this->vertices = vertices;
}

void Mesh::setIndices(const std::vector<int3>& indices)
{
	this->indices = indices;
}

void Mesh::setColor(const float3& color)
{
	this->color = new float3(color);
	isTriangleColors = false;
}

void Mesh::setColors(float3* triangleColors)
{
	color = triangleColors;
	isTriangleColors = true;
}

Mesh::Mesh()
{
	setColor({ 1, 0, 0 });
	texture = nullptr;
}

Mesh::~Mesh()
{
	if (!isTriangleColors)
	{
		delete color;
	}
}

Mesh* Mesh::create(const std::string& fileName)
{
	ObjParser parser;

	std::vector<Triangle> triangles;
	parser.parse(fileName, triangles);

	std::vector<Vertex> vertices(triangles.size() * 3);
	std::vector<int3> indices(triangles.size());

	for (size_t i = 0; i < triangles.size(); ++i)
	{
		int ii = 3 * i;

		auto t = triangles[i];
		vertices[ii] = t.v1;
		vertices[ii + 1] = t.v2;
		vertices[ii + 2] = t.v3;

		indices[i] = int3{ ii, ii + 1, ii + 2 };
	}

	auto m = new Mesh();
	m->setVertices(vertices);
	m->setIndices(indices);

	return m;
}

void Mesh::calculateNormals()
{
	for (auto index : indices)
	{
		Vertex& v1 = vertices[index.a];
		Vertex& v2 = vertices[index.b];
		Vertex& v3 = vertices[index.c];

		auto t = Triangle {v1, v2, v3};
		t.calculateNormals();

		v1.normal = t.n1;
		v2.normal = t.n2;
		v3.normal = t.n3;
	}
}

void Mesh::setTexture(struct Texture* texture)
{
	this->texture = texture;
}
