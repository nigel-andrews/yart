#include "sphere.h"

#include <glm/geometric.hpp>

namespace yart
{
    std::optional<glm::vec3> sphere::intersect(ray r) const
    {
        const auto ray_to_center = position - r.origin;

        const auto a = glm::dot(r.direction, r.direction);
        const auto b = -2.f * glm::dot(r.direction, ray_to_center);
        const auto c = glm::dot(ray_to_center, ray_to_center) - radius * radius;

        const auto discriminant = b * b - 4.f * a * c;

        if (discriminant < 0)
        {
            return {};
        }

        const auto t = (-b - std::sqrt(discriminant)) / (2.f * a);

        const auto intersection_point = r[t];
        const auto normal = glm::normalize(intersection_point - position);

        return (normal + 1.f) / 2.f;
    }
} // namespace yart
