#pragma once

#include "object.h"

struct plane : object
{
    glm::vec3 normal;

    plane() = default;
    plane(const glm::vec3& position, const glm::vec3& normal)
        : object(position)
        , normal(normal)
    {}

    std::optional<float> intersect(ray r) const final;
    glm::vec3 get_normal_at(const glm::vec3&) const final
    {
        return normal;
    }
};
