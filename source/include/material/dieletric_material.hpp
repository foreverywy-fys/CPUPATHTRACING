#pragma once

#include <glm/glm.hpp>
#include "material/microfacet_theory.hpp"
#include "material.hpp"

class DieletricMaterial : public Material
{
public:
    DieletricMaterial(float ior, const glm::vec3 &albedo, float alpha_x = 0, float alpha_z = 0) 
        : ior(ior), albedo_r(albedo), albedo_t(albedo), microfacet_theory(alpha_x, alpha_z) {}
    DieletricMaterial(float ior, const glm::vec3 &albedo_r, const glm::vec3 &albedo_t, float alpha_x = 0, float alpha_z = 0) 
        : ior(ior), albedo_r(albedo_r), albedo_t(albedo_t), microfacet_theory(alpha_x, alpha_z) {}
    virtual std::optional<BSDFSample> sampleBSDF(const glm::vec3 &hit_point, const glm::vec3 &view_direction, const RNG &rng) const override;
private:
    float ior;
    glm::vec3 albedo_r, albedo_t;
    MicroFacetTheory microfacet_theory;
};
