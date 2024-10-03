#pragma once

#include <optional>
#include <glm/vec3.hpp>

#include "ray.h"

namespace yart
{
    struct object
    {
        virtual ~object() = default;
        virtual std::optional<glm::vec3> intersect(ray r) const = 0;
    };
} // namespace yart
