#include "sphere.h"

#include <glm/geometric.hpp>

namespace yart
{
    std::optional<glm::vec3> sphere::intersect(ray r) const
    {
        const auto ray_to_center = position - r.direction;

        const auto a = glm::dot(r.direction, r.direction);
        const auto b = -2.f * glm::dot(r.direction, ray_to_center);
        const auto c = glm::dot(ray_to_center, ray_to_center) - radius * radius;

        const auto discriminant = b * b - 4.f * a * c;

        if (discriminant < 0)
        {
            return {};
        }

        return glm::vec3{1.f};
    }
} // namespace yart
