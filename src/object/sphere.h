#pragma once

#include "object.h"

namespace yart
{
    struct sphere : object
    {
        float radius;

        sphere() = default;
        sphere(const glm::vec3& position, float radius)
            : object(position)
            , radius(radius)
        {}

        std::optional<float> intersect(ray r) const final;
        glm::vec3
        get_normal_at(const glm::vec3& intersection_point) const final;
    };
} // namespace yart
