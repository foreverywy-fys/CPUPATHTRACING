#pragma once

#include "accelerate/bounds.hpp"
#include "shape/shape.hpp"
#include <glm/glm.hpp>

struct Triangle : public Shape
{
    Triangle(
        const glm::vec3& p0,
        const glm::vec3& p1,
        const glm::vec3& p2,
        const glm::vec3& n0,
        const glm::vec3& n1,
        const glm::vec3& n2)
        : p0(p0)
        , p1(p1)
        , p2(p2)
        , n0(n0)
        , n1(n1)
        , n2(n2)
    {
    }

    Triangle(
        const glm::vec3& p0,
        const glm::vec3& p1,
        const glm::vec3& p2)
        : p0(p0)
        , p1(p1)
        , p2(p2)
    {
        const glm::vec3 edge1 = p1 - p0;
        const glm::vec3 edge2 = p2 - p0;
        const glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));
        n0 = normal;
        n1 = normal;
        n2 = normal;
    }

    std::optional<HitInfo> intersect(const Ray &ray, float t_min, float t_max) const override;
    glm::vec3 p0, p1, p2;
    glm::vec3 n0, n1, n2;

    Bounds getBounds() const override 
    {
        Bounds bounds{};
        bounds.expand(p0);
        bounds.expand(p1);
        bounds.expand(p2);
        return bounds;
    }

};
