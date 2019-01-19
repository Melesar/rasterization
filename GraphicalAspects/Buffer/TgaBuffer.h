#pragma once

#include <utils.h>
#include "ITgaSavable.h"
#include "Buffer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <bitset>

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

	enum PixelsOrigin
	{
		BottomLeft, BottomRight, TopLeft, TopRight
	};

	struct TgaHeader
	{
		char identifierLength;
		bool colorMapExists;

		ImageType imageType;

		short colorMapIndex;
		short colorMapLength;
		char colorMapElementSize;

		short x;
		short y;
		short width;
		short height;
		ImageDepth colorDepth;

		char imageDescriptor;

		short getAlphaSize() const;
		void setAlphaSize(short size);

		PixelsOrigin  getPixelsOrigin() const;
		void setPixelsOrigin(PixelsOrigin origin);

		TgaHeader ();
	};

	TgaHeader header;

	void parseHeader (std::istream& s, TgaHeader& h);

	friend std::ostream& operator << (std::ostream& s, const TgaHeader& h);
};
