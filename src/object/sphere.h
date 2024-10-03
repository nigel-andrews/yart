#pragma once

#include "object.h"

namespace yart
{
    struct sphere : object
    {
        glm::vec3 position;
        float radius;

        std::optional<glm::vec3> intersect(ray r) const final;
    };
} // namespace yart
