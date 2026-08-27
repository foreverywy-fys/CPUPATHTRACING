#pragma once

#include "until/rng.hpp"
#include <glm/glm.hpp>

class MicroFacetTheory
{
    // Smith Models
    // GGX Distribution
    // Stretching Invariance
public:
    MicroFacetTheory(float alpha_x, float alpha_z);
    float normalDistribution(const glm::vec3 &microfacet_normal) const;
    float masking(const glm::vec3 &view_direction, const glm::vec3 &microfacet_normal) const;
    float heightCorrelatedMaskingShadowing(const glm::vec3 &light_direction, const glm::vec3 &view_direction, const glm::vec3 &microfacet_normal) const;
    bool isDeltaDistribution() const;

    float visibleNormalDistribution(const glm::vec3 &view_direction, const glm::vec3 &microfacet_normal) const;
    glm::vec3 sampleVisibleNormal(const glm::vec3 &view_direction, const RNG &rng) const;
private:
    float slopeDistribution(const glm::vec2 &slope) const;
    float Lambda(const glm::vec3 &direction_upper) const;
    float alpha_x {};
    float alpha_z {};  
};
