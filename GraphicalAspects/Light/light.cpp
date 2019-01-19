#include "light.h"
#include <cmath>

float3 DirectionalLight::getDirection(const float3 &viewPoint) const
{
    return vp.world2View(position, true);
}

float3 Light::calculate(const Triangle &t, float l1, float l2, float l3)
{
    auto point = t.getPosition(l1, l2, l3);
    auto dir = getDirection(point);
    auto normal = t.getNormal(l1, l2, l3);
    double cosine = dot(dir, normal);
    cosine = std::fmax(cosine, 0);

    auto r = normal * 2 * dot(normal, dir) - dir;
    auto spec = dot(r, -vp.getViewDirection());
    spec = std::pow(spec, shininess);

    auto color = ambient + diffuse * cosine + specular * spec;

    return color;
}

DirectionalLight::DirectionalLight(VertexProcessor vp) : Light(vp)
{
    position = vp.obj2World(position);
}

float3 PointLight::getDirection(const float3 &viewPoint) const
{
    return viewPoint - vp.world2View(position, true);
}

PointLight::PointLight(VertexProcessor vp) : Light(vp)
{
    position = vp.obj2World(position);
}
