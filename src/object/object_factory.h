#pragma once

#include <memory>

#include "object/plane.h"
#include "object/sphere.h"

namespace factory
{
    static inline std::unique_ptr<sphere> make_sphere(const glm::vec3& pos,
                                                      float radius)
    {
        return std::make_unique<sphere>(pos, radius);
    }

    static inline std::unique_ptr<plane> make_plane(const glm::vec3& pos,
                                                    const glm::vec3& normal = {
                                                        0.f, 1.f, 0.f })
    {
        return std::make_unique<plane>(pos, normal);
    }
} // namespace factory
