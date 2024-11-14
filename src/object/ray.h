#pragma once

#include <glm/vec3.hpp>

struct ray
{
    glm::vec3 origin;
    glm::vec3 direction;

    constexpr glm::vec3 at(float t) const
    {
        return origin + t * direction;
    }

    constexpr glm::vec3 operator[](float t) const
    {
        return at(t);
    }
};
