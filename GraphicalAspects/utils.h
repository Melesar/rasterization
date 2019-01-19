#pragma once
#include "Data/math_structs.h"
#include <complex>

const float PI = 3.14159265358979323846f;

const float3 UNIDENTIFIED_NORMAL = {0, 0, 0};

enum ImageDepth {NoAlpha = 24, WithAlpha = 32};

inline float clamp01 (float v)
{
	return v < 0 ? 0 : v > 1.f ? 1.f : v;
}

inline unsigned int colorToInt(const float3 &color, bool withAlpha = true)
{
	auto red = static_cast<int>(clamp01(color.r) * 255);
	auto green = static_cast<int>(clamp01(color.g) * 255);
	auto blue = static_cast<int>(clamp01(color.b) * 255);

	red = red << 16 & 0x00FF0000;
	green = green << 8 & 0x0000FF00;
	blue = blue & 0x000000FF;

	auto result = red | green | blue;
	if (withAlpha) {
	    result = result | 0xFF000000;
	}

	return static_cast<unsigned int>(result);
}

inline float3 intToColor(unsigned v)
{
	int red = (v & 0x00FF0000) >> 16;
    int green = (v & 0x0000FF00) >> 8;
    int blue = (v & 0x000000FF);
    float multiplier = 1.f / 255;

	return multiplier * float3{(float) red, (float) green, (float) blue};
}

inline int clamp (int value, int min, int max)
{
	return value > max ? max : value < min ? min : value;
}