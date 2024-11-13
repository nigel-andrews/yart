#pragma once

#include <glm/vec3.hpp>
#include <memory>
#include <optional>

#include "material.h"
#include "ray.h"

struct object
{
    constexpr object() = default;
    explicit constexpr object(const glm::vec3& pos)
        : position(pos)
    {}

    virtual ~object() = default;

    // FIXME: Hit infos to record intersection information
    virtual std::optional<float> intersect(ray r) const = 0;

    // TODO: Remove since hit infos will store the relevant information
    virtual glm::vec3
    get_normal_at(const glm::vec3& intersection_point) const = 0;

    // NOTE: Positions as a concept for object is independent to its type so
    //       that is why they are public in the base class (+ will be movable
    //       so it's not an invariant)
    glm::vec3 position;
    // Public for now (quick modif of materials)
    material mat;
};
