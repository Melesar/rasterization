#pragma once

#include <utils.h>
#include "ITgaSavable.h"
#include "Buffer.h"

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
};
