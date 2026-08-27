#pragma once

#include "material.hpp"
#include "material/microfacet_theory.hpp"

class ConductorMaterial : public Material
{
public:
    ConductorMaterial(const glm::vec3 &ior, const glm::vec3 &k, float alpha_x = 0, float alpha_z = 0)
        : ior(ior), k(k) , microfacet_theory(alpha_x, alpha_z) {}
    virtual std::optional<BSDFSample> sampleBSDF(const glm::vec3 &hit_point, const glm::vec3 &view_direction, const RNG &rng) const override;
private:
    glm::vec3 ior;
    glm::vec3 k;
    MicroFacetTheory microfacet_theory;
};
