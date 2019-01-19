#pragma once

#include <string>

class ITgaSavable
{
public:
	virtual void save(const std::string& fileName) = 0;
};