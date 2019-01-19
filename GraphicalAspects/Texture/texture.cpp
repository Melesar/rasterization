
#include <Buffer/TgaBuffer.h>
#include <utils.h>
#include "texture.h"

Texture::Texture(const std::string &filename)
{
    buffer = std::make_unique<TgaBuffer>(filename);
}

int Texture::width() const
{
    return buffer->width();
}

int Texture::height() const
{
    return buffer->height();
}

float3 Texture::sample(float u, float v)
{
    int x = clamp(u * width(), 0, width() - 1);
    int y = clamp(v * height(), 0, height() - 1);

    const auto value = buffer->read(x, y);
    return intToColor(value);
}

void Texture::save(const std::string &filename)
{
    auto savable = dynamic_cast<ITgaSavable*>(buffer.get());
    if (savable != nullptr){
        savable->save(filename);
    }
}

