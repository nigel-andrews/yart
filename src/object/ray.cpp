#include "ray.h"

#include <random>

#include "glm/geometric.hpp"

namespace
{
    float randf()
    {
        static std::uniform_real_distribution<float> distribution(-1.f, 1.f);
        static std::mt19937 generator;

        return distribution(generator);
    }

    glm::vec3 randvec3()
    {
        glm::vec3 result;

        do
        {
            result.x = randf();
            result.y = randf();
            result.z = randf();
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
