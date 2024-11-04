#include "plane.h"

#include <glm/geometric.hpp>

std::optional<float> plane::intersect(ray r) const
{
    auto b = glm::dot(r.direction, normal);

    if (!b)
    {
        return {};
    }

    auto a = glm::dot((position - r.origin), normal);
    float t = a / b;
    if (t < 0)
        return {};

    return t;
}
