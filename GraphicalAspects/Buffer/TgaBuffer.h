#pragma once

#include <utils.h>
#include "ITgaSavable.h"
#include "Buffer.h"
#include <fstream>
#include <iostream>
#include <iomanip>

class TgaBuffer : public Buffer, public ITgaSavable
{
public:
	TgaBuffer(int width, int height);
	TgaBuffer(const std::string& fileName);

	void save(const std::string& fileName) override;

	void flush() override;

protected:
	unsigned int convertColor(const float3 &color) const override;

private:
	std::string _filename;
	ImageDepth depth;

	enum ImageType : char
	{
		NoImage,
		WithPaletteNoCompression, TrueColorNoCompression, MonochromaticNoCompression,
		WithPalette = 9, TrueColor, Monochromatic
	};

	struct TgaHeader
	{
		char identifierLength;
		bool colorMapExists;

		short colorMapIndex;
		short colorMapLength;
		char colorMapElementSize;

		ImageType imageType;

		ImageDepth colorDepth;
		short x, y;
		short width, height;

		char imageDescriptor;

		int getAlphaSize() const
		{

		}

		bool isLeftRight() const
		{

		}
	};

	void parseHeader (std::ifstream& s, TgaHeader& h);

	friend std::ostream& operator << (std::ostream& s, const TgaHeader& h);
};
