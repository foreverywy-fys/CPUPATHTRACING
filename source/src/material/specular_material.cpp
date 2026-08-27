#include "material/specular_material.hpp"
#include <glm/glm.hpp>

std::optional<BSDFSample> SpecularMaterial::sampleBSDF(const glm::vec3 &hit_point, const glm::vec3 &view_direction, const RNG &rng) const
{
    glm::vec3 light_direction  { -view_direction.x, view_direction.y, -view_direction.z };
    return BSDFSample
    {
        albedo / glm::abs(light_direction.y),
        1.f,
        light_direction
    };
}
