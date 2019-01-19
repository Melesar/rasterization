#include "Buffer.h"
#include "../utils.h"
#include <fstream>
#include <memory>

void Buffer::setSize(int x, int y, int width, int height)
{
	_minX = x;
	_minY = y;
	_maxX = x + width;
	_maxY = y + height;
	this->_width = width;
	this->_height = height;

	const auto newLength = width * height;
	if (this->_length != newLength)
	{
		delete[] _color;
		_color = new unsigned[newLength];

		delete[] _depth;
		_depth = new float[newLength];

		_length = width * height;

		clearColor();
		clearDepth();
	}
}

void Buffer::clearColor(const float3 & value) const
{
	for (int i = 0; i < _length; ++i) { _color[i] = colorToInt(value); }
}

void Buffer::clearDepth(float value) const
{
	for (int i = 0; i < _length; ++i) { _depth[i] = value; }
}

void Buffer::write(int x, int y, float z, float3 color) const
{
	const auto index = x + y * _width;
	const auto depth = _depth[index];
	if (z > depth) {
		_color[index] = convertColor(color);
		_depth[index] = z;
	}
}

Buffer::Buffer(int x, int y, int width, int height)
{
	_color = new unsigned[1];
	_depth = new float[1];

	setSize(x, y, width, height);
	clearColor();
	clearDepth();
}

unsigned Buffer::read(int x, int y) const
{
	auto index = y * width() + x;
    return _color[index];
}
