#include <optional>
#include "shape/sphere.hpp"

std::optional<HitInfo> Sphere::intersect(const Ray &ray, float t_min, float t_max) const
{
    glm::vec3 co = ray.origin -center;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0F * glm::dot(ray.direction, co);
    float c = glm::dot(co, co) - radius * radius;
    float delta = b * b - 4.0F * a * c;
    if (delta < 0.0F)
    {
        return {};
    }
    const float sqrt_delta = glm::sqrt(delta);
    float hit_t = (-b - sqrt_delta) * 0.5F / a;
    if (hit_t <= t_min)
    {
        hit_t = (-b + sqrt_delta) * 0.5F / a;
    }
    if (hit_t > t_min && hit_t < t_max)
    {
        glm::vec3 hit_point = ray.hit(hit_t);
        glm::vec3 normal = glm::normalize(hit_point - center);
        return HitInfo { hit_t, hit_point, normal};
    }
    return {};
}
