#pragma once
#include "mesh.h"

class ConeMesh : public Mesh
{
private:

	float radius;
	float height;
	int resolution;

public:

	ConeMesh(float radius, float height, int resolution = 32);

private:

	void makeVertices();
	void makeIndices();
};
