#pragma once

#include <Data/math_structs.h>
#include <Data/Triangle.h>
#include "VertexProcessor/VertexProcessor.h"

class Light
{
public:

    float3 position;

    float3 ambient;
    float3 diffuse;
    float3 specular;

    float shininess;

    virtual float3 getDirection (const float3& viewPoint) const = 0;

    float3 calculate (const Triangle& t, float l1, float l2, float l3);

protected:

    explicit Light(VertexProcessor vp)
        : vp(vp), position({0, 0, 0}), ambient({0.4f, 0, 0.2f}),
          diffuse ({0.5f, 0.5f, 0.5f}), specular({0.5f, 0.5f, 0.5f}),
          shininess(4.f)
    {}

    VertexProcessor vp;
};

class DirectionalLight : public Light
{
public:

    float3 getDirection(const float3 &viewPoint) const override;

    explicit DirectionalLight(VertexProcessor vp);
};

class PointLight : public Light
{
public:

    float3 getDirection(const float3 &viewPoint) const override;

    explicit PointLight(VertexProcessor vp);
};
