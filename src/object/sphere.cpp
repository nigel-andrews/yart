#include "sphere.h"

#include <glm/geometric.hpp>

std::optional<float> sphere::intersect(ray r) const
{
    const auto ray_to_center = position - r.origin;

    // TODO: simplify equation
    const auto a = glm::dot(r.direction, r.direction);
    const auto b = -2.f * glm::dot(r.direction, ray_to_center);
    const auto c = glm::dot(ray_to_center, ray_to_center) - radius * radius;

    const auto discriminant = b * b - 4.f * a * c;

    if (discriminant < 0)
        return {};

    float root = (-b - std::sqrt(discriminant)) / (2.f * a);

    if (root < 0.f)
        return {};

    return root;
}

glm::vec3 sphere::get_normal_at(const glm::vec3& intersection_point) const
{
    return glm::normalize(intersection_point - position);
}
