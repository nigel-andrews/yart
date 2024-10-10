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

        // Don't really care about encapsulating this struct, it's easier
        // to have this public
        struct
        {
            glm::vec3 albedo = glm::vec3{ 1.f };
            // TODO: metalness, roughness, other kinds of -nesses
        } material;
    };
} // namespace yart
