#include "accelerate/bounds.hpp"
#include <algorithm>
#include <cmath>

bool Bounds::hasIntersection(const Ray &ray, float t_min, float t_max) const
{
    for (int axis = 0; axis < 3; ++axis)
    {
        const float origin = ray.origin[axis];
        const float direction = ray.direction[axis];

        if (std::abs(direction) < 1.0e-8F)
        {
            if (origin < b_min[axis] || origin > b_max[axis])
            {
                return false;
            }
            continue;
        }

        float t0 = (b_min[axis] - origin) / direction;
        float t1 = (b_max[axis] - origin) / direction;
        if (t0 > t1)
        {
            std::swap(t0, t1);
        }

        t_min = std::max(t_min, t0);
        t_max = std::min(t_max, t1);
        if (t_min > t_max)
        {
            return false;
        }
    }

    return true;
}

bool Bounds::hasIntersection(const Ray &ray, const glm::vec3 &inv_direction, float t_min, float t_max) const
{
    for (int axis = 0; axis < 3; ++axis)
    {
        const float origin = ray.origin[axis];
        const float direction = ray.direction[axis];

        if (std::abs(direction) < 1.0e-8F)
        {
            if (origin < b_min[axis] || origin > b_max[axis])
            {
                return false;
            }
            continue;
        }

        const float inverse = inv_direction[axis];
        float t0 = (b_min[axis] - origin) * inverse;
        float t1 = (b_max[axis] - origin) * inverse;
        if (t0 > t1)
        {
            std::swap(t0, t1);
        }

        t_min = std::max(t_min, t0);
        t_max = std::min(t_max, t1);
        if (t_min > t_max)
        {
            return false;
        }
    }

    return true;
}
