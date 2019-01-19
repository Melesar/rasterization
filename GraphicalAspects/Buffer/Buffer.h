#pragma once

#include "../Data/math_structs.h"

class Buffer
{
protected:
	unsigned *_color;
	float *_depth;

	int _width, _height, _minX, _maxX, _minY, _maxY, _length;

public:
	void setSize(int x, int y, int width, int height);

	void clearColor(const float3& value = float3 {1, 1, 1}) const;
	void clearDepth(float value = 0) const;

	virtual void flush() = 0;

	int width() const { return _width; }
	int height() const { return _height; }

	void write(int x, int y, float z, float3 color) const;
	unsigned read(int x, int y) const;

protected:
	Buffer(int x, int y, int width, int height);

	virtual unsigned convertColor (const float3& color) const = 0;
};
