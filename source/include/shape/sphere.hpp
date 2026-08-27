#pragma once

#include "accelerate/bounds.hpp"
#include "shape/shape.hpp"
#include <glm/glm.hpp>

struct Sphere : public Shape
{
    Sphere (const glm::vec3 &center, float radius) : center(center), radius(radius) {}
    std::optional<HitInfo> intersect(const Ray &ray, float t_min, float t_max) const override;
    glm::vec3 center;
    float radius;
    Bounds getBounds() const override { return {center - radius, center + radius}; }
};
