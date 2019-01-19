#include "TgaBuffer.h"


TgaBuffer::TgaBuffer(int width, int height)
	: Buffer (0, 0, width, height)
{
    header.width = width;
    header.height = height;
}

void TgaBuffer::save(const std::string& fileName)
{
	_filename = fileName;
	flush();
}

void TgaBuffer::flush()
{
	std::ofstream f(_filename, std::ios::out | std::ios::binary);

	std::cout << "Actual image header: " << std::endl << header << std::endl;

	unsigned short header[] = {
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		_width, _height,
		0x0820
	};

	f.write(reinterpret_cast<char*>(header), 2 * 9);
	f.write(reinterpret_cast<char*>(_color), 4 * _length);
	
	f.close();

	std::ofstream oHeader ("header.dat");
	oHeader.write(reinterpret_cast<char*>(&this->header), 18);
	oHeader.close();

	std::ifstream iHeader("header.dat");
	TgaHeader hh;
	parseHeader(iHeader, hh);
	std::cout << "Written header: " << std::endl << hh << std::endl;
	std::cin.get();
}

TgaBuffer::TgaBuffer(const std::string &fileName) : Buffer (0, 0, 0, 0)
{
	std::ifstream f(fileName, std::ios::binary);
	parseHeader(f, header);

	int width = header.width;
	int height = header.height;

	std::cout << fileName << std::endl << header << std::endl;

	setSize(0, 0, width, height);
	clearDepth();

	auto pixelSize = header.colorDepth >> 3;
	auto bufferSize = width * height * pixelSize;
    auto buffer = std::make_unique<unsigned char[]>((size_t) bufferSize);
    f.read(reinterpret_cast<char*>(buffer.get()), bufferSize);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int index = 18 + pixelSize * (width * i + j);
			unsigned b = buffer[index + 0] & 0xFF;
			unsigned g = buffer[index + 1] & 0xFF;
			unsigned r = buffer[index + 2] & 0xFF;
			unsigned a = 0xFF;

			_color[width * (height - i - 1) + (width - j - 1)] =
					(r << 16) | (g << 8) | b | (a << 24);
		}
	}
}

void TgaBuffer::parseHeader(std::istream &s, TgaHeader &h)
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
	return colorToInt(color);
}

std::ostream& operator<<(std::ostream &s, const TgaBuffer::TgaHeader &h)
{
	s << "Identifier length: " << (int) h.identifierLength << std::endl;
	s << "Color map exists: " << h.colorMapExists << std::endl;
	s << "Image type: " << h.imageType << std::endl;
	s << std::endl;

	//if (h.colorMapExists) {
		s << "Color map index: " << h.colorMapIndex << std::endl;
		s << "Color map length: " << h.colorMapLength << std::endl;
		s << "Color map element size: " << (int) h.colorMapElementSize << std::endl;
		s << std::endl;
	//}

	s << "X position: " << h.x << std::endl;
	s << "Y position: " << h.y << std::endl;
	s << "Width: " << h.width << std::endl;
	s << "Height: " << h.height << std::endl;
	s << "Image depth: " << h.colorDepth << std::endl;
	s << "Alpha size: " << h.getAlphaSize() << std::endl;
	s << "Pixels origin: " << h.getPixelsOrigin() << std::endl;

	return s;
}

short TgaBuffer::TgaHeader::getAlphaSize() const
{
	std::bitset<8> b(imageDescriptor);
	return b[3] | b[2] | b[1] | b[0];
}

void TgaBuffer::TgaHeader::setAlphaSize(short size)
{
	std::bitset<8> alpha (size);
	std::bitset<8> desc (imageDescriptor);
	desc[0] = alpha[0];
	desc[1] = alpha[1];
	desc[2] = alpha[2];
	desc[3] = alpha[3];

	imageDescriptor = (char) desc.to_ulong();
}

TgaBuffer::PixelsOrigin TgaBuffer::TgaHeader::getPixelsOrigin() const
{
	std::bitset<8> b (imageDescriptor);

	auto b4 = b[4];
	auto b5 = b[5];
	if (!b5 && !b4){
		return BottomLeft;
	}
	if (!b5 && b4) {
		return BottomRight;
	}
	if (b5 && !b4) {
		return TopLeft;
	}

	return TopRight;
}

void TgaBuffer::TgaHeader::setPixelsOrigin(TgaBuffer::PixelsOrigin origin)
{
	std::bitset<8> b (imageDescriptor);
	switch (origin) {

		case BottomLeft:
			b[4] = b[5] = false;
			break;
		case BottomRight:
			b[5] = false;
			b[4] = true;
			break;
		case TopLeft:
			b[5] = true;
			b[4] = false;
			break;
		case TopRight:
			b[4] = b[5] = true;
			break;
	}

	imageDescriptor = (char) b.to_ulong();
}

TgaBuffer::TgaHeader::TgaHeader()
{
	identifierLength = colorMapExists = colorMapElementSize = imageDescriptor = 0;
	colorMapIndex = colorMapLength = x = y = width = height = 0;
	colorDepth = ImageDepth::WithAlpha;
	imageType = ImageType::TrueColorNoCompression;

	setAlphaSize(1);
	setPixelsOrigin(PixelsOrigin::BottomLeft);
}
