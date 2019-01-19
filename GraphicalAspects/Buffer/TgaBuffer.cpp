#include "TgaBuffer.h"
#include <fstream>
#include <iostream>
#include <iomanip>

TgaBuffer::TgaBuffer(int width, int height)
	: Buffer (0, 0, width, height)
{
    depth = WithAlpha;
}

void TgaBuffer::save(const std::string& fileName)
{
	_filename = fileName;
	flush();
}

void TgaBuffer::flush()
{
	std::ofstream f(_filename, std::ios::out | std::ios::binary);
	
	unsigned short header[] = {
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		_width, _height,
		0x0820
	};
	
	f.write(reinterpret_cast<char*>(header), 2 * 9);
	f.write(reinterpret_cast<char*>(_color), 4 * _length);
	
	f.close();
}

TgaBuffer::TgaBuffer(const std::string &fileName) : Buffer (0, 0, 0, 0)
{
	std::ifstream f(fileName, std::ios::binary);
	f.ignore(12);

	int width, height;
	f.read((char*)&width, 2);
	f.read((char*)&height, 2);

	short d;
	f.read((char*)&d, 1);
	depth = static_cast<ImageDepth>(d);
    f.ignore(1);

	setSize(0, 0, width, height);
	clearDepth();

    for (int i = 0; i < _length; ++i) {
        unsigned c;
        f.read((char*)&c, depth / 8);
        _color[i] = c;
    }
}

unsigned int TgaBuffer::convertColor(const float3 &color) const
{
	return colorToInt(color, depth == WithAlpha);
}
