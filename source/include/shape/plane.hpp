#pragma once

#include "shape/shape.hpp"
#include <glm/glm.hpp>

struct Plane : public Shape
{
    Plane(const glm::vec3 &point, const glm::vec3 &normal) : point(point), normal(glm::normalize(normal)) {}
    glm::vec3 point;
    glm::vec3 normal;

    std::optional<HitInfo> intersect(const Ray &ray, float t_min, float t_max) const override;
};
