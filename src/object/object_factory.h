#pragma once

#include <memory>

#include "object/sphere.h"
#include "utils/singleton.h"

namespace yart
{
    class factory : utils::singleton<factory>
    {
    public:
        static std::unique_ptr<sphere> make_sphere(const glm::vec3& pos,
                                                   float radius)
        {
            return std::make_unique<sphere>(pos, radius);
        }
    };
} // namespace yart
