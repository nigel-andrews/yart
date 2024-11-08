#include "ray.h"

#include "glm/geometric.hpp"
#include "utils/misc.h"

namespace
{
    glm::vec3 randvec3()
    {
        glm::vec3 result;

        do
        {
            result.x = utils::randf();
            result.y = utils::randf();
            result.z = utils::randf();
        } while (glm::length(result) == 0.f || glm::length(result) > 1.f);

        return glm::normalize(result);
    }
} // namespace

glm::vec3 ray::hemisphere_ray_direction(const glm::vec3& normal)
{
    auto ray = randvec3();

    if (glm::dot(ray, normal) < 0.f)
        ray *= -1.f;

    return ray;
}
