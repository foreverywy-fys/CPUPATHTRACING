#pragma once

#include <glm/glm.hpp>
#include "material/material.hpp"

class SpecularMaterial : public Material
{
public:
    SpecularMaterial(const glm::vec3 &albedo) : albedo(albedo) {}
    virtual std::optional<BSDFSample> sampleBSDF(const glm::vec3 &hit_point, const glm::vec3 &view_direction, const RNG &rng) const override;
private:
    glm::vec3 albedo {};
};
