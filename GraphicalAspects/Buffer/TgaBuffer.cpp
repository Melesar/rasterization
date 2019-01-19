#include "TgaBuffer.h"


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
	TgaHeader header;
	parseHeader(f, header);

	int width = header.width;
	int height = header.height;
	depth = header.colorDepth;

	std::cout << header << std::endl;

//	f.ignore(12);
//
//	int width, height;
//	f.read((char*)&width, 2);
//	f.read((char*)&height, 2);
//
//	short d;
//	f.read((char*)&d, 1);
//	depth = static_cast<ImageDepth>(d);
//    f.ignore(1);

	setSize(0, 0, width, height);
	clearDepth();

    for (int i = 0; i < _length; ++i) {
        unsigned c;
        f.read((char*)&c, depth / 8);
        _color[i] = c;
    }
}

void TgaBuffer::parseHeader(std::ifstream &s, TgaHeader &h)
{
	s.read(&h.identifierLength, 1);

	s.read(reinterpret_cast<char*>(&h.colorMapExists), 1);
	s.read(reinterpret_cast<char*>(&h.imageType), 1);

	s.read(reinterpret_cast<char*>(&h.colorMapIndex), 2);
	s.read(reinterpret_cast<char*>(&h.colorMapLength), 2);
	s.read(&h.colorMapElementSize, 1);

	s.read(reinterpret_cast<char*>(&h.x), 2);
	s.read(reinterpret_cast<char*>(&h.y), 2);
	s.read(reinterpret_cast<char*>(&h.width), 2);
	s.read(reinterpret_cast<char*>(&h.height), 2);
	s.read(reinterpret_cast<char*>(&h.colorDepth), 1);
	s.read(&h.imageDescriptor, 1);


}

unsigned int TgaBuffer::convertColor(const float3 &color) const
{
	return colorToInt(color, depth == WithAlpha);
}

std::ostream& operator<<(std::ostream &s, const TgaBuffer::TgaHeader &h)
{
	s << "Identifier length: " << (int) h.identifierLength << std::endl;
	s << "Image type: " << h.imageType << std::endl;
	s << std::endl;

	if (h.colorMapExists) {
		s << "Color map index: " << h.colorMapIndex << std::endl;
		s << "Color map length: " << h.colorMapLength << std::endl;
		s << "Color map element size: " << (int) h.colorMapElementSize << std::endl;
		s << std::endl;
	}

	s << "X position: " << h.x << std::endl;
	s << "Y position: " << h.y << std::endl;
	s << "Width: " << h.width << std::endl;
	s << "Height: " << h.height << std::endl;
	s << "Image depth: " << h.colorDepth << std::endl;
	s << "Alpha size: " << h.getAlphaSize() << std::endl;
	s << "Pixel order: " << (h.isLeftRight() ? "Left to righ" : "Right to left") << std::endl;

	return s;
}
