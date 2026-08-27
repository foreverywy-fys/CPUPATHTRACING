#pragma once

#include <glm/glm.hpp>
#include "material/material.hpp"

class DiffuseMaterial : public Material
{
public:
    DiffuseMaterial(const glm::vec3 &albedo) : albedo(albedo) {}
    virtual std::optional<BSDFSample> sampleBSDF(const glm::vec3 &hit_point, const glm::vec3 &view_direction, const RNG &rng) const override;
private:
    glm::vec3 albedo {};
};
