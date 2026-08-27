#include "shape/triangle.hpp"

#include <cmath>

std::optional<HitInfo> Triangle::intersect(const Ray& ray, float t_min, float t_max) const
{
    const glm::vec3 e1 = p1 - p0;
    const glm::vec3 e2 = p2 - p0;
    const glm::vec3 s1 = glm::cross(ray.direction, e2);
    const float determinant = glm::dot(s1, e1);

    if (std::abs(determinant) < 1.0e-8F)
    {
        return {};
    }

    const float inv_determinant = 1.0F / determinant;
    const glm::vec3 s = ray.origin - p0;
    const float u = glm::dot(s1, s) * inv_determinant;
    if (u < 0.0F || u > 1.0F)
    {
        return {};
    }

    const glm::vec3 s2 = glm::cross(s, e1);
    const float v = glm::dot(s2, ray.direction) * inv_determinant;
    if (v < 0.0F || u + v > 1.0F)
    {
        return {};
    }

    const float hit_t = glm::dot(s2, e2) * inv_determinant;
    if (hit_t > t_min && hit_t < t_max)
    {
        const glm::vec3 hit_point = ray.hit(hit_t);
        const glm::vec3 normal = (1.0F - u - v) * n0 + u * n1 + v * n2;
        return HitInfo { hit_t, hit_point, glm::normalize(normal) };
    }

    return {};
}
