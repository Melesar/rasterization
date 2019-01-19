#include "Rasterizer.h"
#include "../Buffer/Buffer.h"
#include "../utils.h"
#include "Light/light.h"
#include "Texture/texture.h"

void Rasterizer::triangle(const Triangle& tr, VertexProcessor& vp, Texture* texture) const
{
	const auto width = buffer->width();
	const auto height = buffer->height();

	auto t = vp.triangleToProjection(tr);
	const auto maxX = clamp(transform01(t.maxX()) * width, 0, width);
	const auto maxY = clamp(transform01(t.maxY()) * height, 0, height);
	const auto minX = clamp(transform01(t.minX()) * width, 0, width);
	const auto minY = clamp(transform01(t.minY()) * height, 0, height);

	const int x1 = transform01(t.p1.x) * width;
	const int x3 = transform01(t.p3.x) * width;
	const int x2 = transform01(t.p2.x) * width;

	const int y1 = transform01(t.p1.y) * height;
	const int y2 = transform01(t.p2.y) * height;
	const int y3 = transform01(t.p3.y) * height;

	const auto dx12 = x1 - x2;
	const auto dx23 = x2 - x3;
	const auto dx31 = x3 - x1;
	const auto dy12 = y1 - y2;
	const auto dy23 = y2 - y3;
	const auto dy31 = y3 - y1;

	const auto tl1 = dy12 < 0 || dy12 == 0 && dx12 > 0;
	const auto tl2 = dy23 < 0 || dy23 == 0 && dx23 > 0;
	const auto tl3 = dy31 < 0 || dy31 == 0 && dx31 > 0;

	const auto l1Den = 1.f / (-dy23 * dx31 + dx23 * dy31);
	const auto l2Den = 1.f / (dy31 * dx23 - dx31 * dy23);

	auto viewTriangle = vp.triangleToView(tr);
	for (int x = minX; x < maxX; ++x)
	{
		for (int y = minY; y < maxY; ++y)
		{
			if ((tl1 ? dx12 * (y - y1) - dy12 * (x - x1) >= 0 : dx12 * (y - y1) - dy12 * (x - x1) > 0) &&
				(tl2 ? dx23 * (y - y2) - dy23 * (x - x2) >= 0 : dx23 * (y - y2) - dy23 * (x - x2) > 0) &&
				(tl3 ? dx31 * (y - y3) - dy31 * (x - x3) >= 0 : dx31 * (y - y3) - dy31 * (x - x3) > 0))
			{
				const auto l1 = (dy23 * (x - x3) - dx23 * (y - y3)) * l1Den;
				const auto l2 = (dy31 * (x - x3) - dx31 * (y - y3)) * l2Den;
				const auto l3 = 1 - l1 - l2;

				const auto depth = t.getDepth(l1, l2, l3);
				const auto fragmentColor = calculateLight(viewTriangle, l1, l2, l3);
				const auto textureSample = sampleTexture(texture, viewTriangle, l1, l2, l3);
				buffer->write(x, y, depth, fragmentColor + textureSample);
			}
		}
	}
}

void Rasterizer::render() const
{
	buffer->flush();
}

float Rasterizer::transform01(float v) const
{
	return (v + 1) * 0.5f;
}

float3 Rasterizer::calculateLight(const Triangle &triangleView, float l1, float l2, float l3) const
{
    float3 result = {0, 0, 0};
    for(auto l : lights) {
        result = result + l->calculate(triangleView, l1, l2, l3);
    }

    return result;
}

void Rasterizer::addLight(class Light *light)
{
	lights.push_back(light);
}

float3 Rasterizer::sampleTexture(struct Texture *texture, const Triangle &t, float l1, float l2, float l3) const
{
	if (texture == nullptr) {
		return t.getColor(l1, l2, l3);
	}

	const auto uv = t.getUV(l1, l2, l3);
	return texture->sample(uv.x, uv.y);
}
