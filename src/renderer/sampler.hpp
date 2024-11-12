#pragma once

#include <glm/vec2.hpp>

// FIXME: This is essentially a uniform sampler and will be factored accordingly
class sampler
{
public:
    sampler(float range_min = -1.f, float range_max = 1.f)
        : domain_(range_min, range_max)
    {}

    glm::vec2 sample2D(const glm::vec2& discrete_coords) const;

private:
    // NOTE: [domain_[0], domain_[1])
    glm::vec2 domain_;
};
