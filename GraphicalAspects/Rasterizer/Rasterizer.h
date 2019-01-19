#pragma once

#include "../Data/Triangle.h"
#include <vector>
#include <VertexProcessor/VertexProcessor.h>

class Rasterizer
{
public:

	void triangle(const Triangle& tr, VertexProcessor& vp, class Texture* texture = nullptr) const;
	void render() const;

	void addLight(class Light* light);

	explicit Rasterizer(class Buffer* buffer) : buffer(buffer){}

private:
	Buffer* buffer;
	std::vector<Light*> lights;

	float transform01(float v) const;
	float3 calculateLight(const Triangle& triangleView, float l1, float l2, float l3) const;
	float3 sampleTexture(class Texture* texture, const Triangle& t, float l1, float l2, float l3) const;
};
