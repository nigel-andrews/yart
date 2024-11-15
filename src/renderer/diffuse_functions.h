#pragma once

#include <cmath>
#include <glm/vec3.hpp>

#include "object/object.h"
#include "utils/view_ptr.h"

namespace diffuse_functions
{
    struct lambertian
    {
        glm::vec3 operator()(utils::view_ptr<object> object,
                             const glm::vec3& /*point*/,
                             const glm::vec3& /*light_direction*/,
                             const glm::vec3& /*view_direction*/)
        {
            return object->mat.albedo / M_PIf;
        }
    };
} // namespace diffuse_functions
