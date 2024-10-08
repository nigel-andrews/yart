#pragma once

#include <glm/vec3.hpp>
#include <optional>

#include "ray.h"

namespace yart
{
    struct object
    {
        virtual ~object() = default;
        virtual std::optional<float> intersect(ray r) const = 0;
        virtual glm::vec3
        get_normal_at(const glm::vec3& intersection_point) const = 0;
    };
} // namespace yart
