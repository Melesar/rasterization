#pragma once

#include <string>
#include <memory>
#include <Data/math_structs.h>

class Texture
{
public:

    Texture (const std::string& filename);

    float3 sample (float u, float v);
    void save(const std::string& filename);

    int width() const;
    int height() const;

private:

    std::unique_ptr<class Buffer> buffer;
};