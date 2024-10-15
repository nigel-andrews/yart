#pragma once

#include <glm/vec3.hpp>

namespace yart::lights
{
    struct point_light
    {
        glm::vec3 position;
        glm::vec3 colour;
        float intensity;
    };
} // namespace yart::lights
