#include "scene.h"

#include <glm/geometric.hpp>

namespace yart
{
    glm::vec3 scene::cast_ray(const ray& ray) const
    {
        float closest_root{ std::numeric_limits<float>::max() };
        object* hit_object = nullptr;

        for (const auto& object : objects_)
        {
            const auto root = object->intersect(ray);

            if (!root)
                continue;

            closest_root = std::min(*root, closest_root);
            hit_object = object.get();
        }

        if (closest_root != std::numeric_limits<float>::max())
        {
            const auto intersection_point =
                ray.origin + closest_root * ray.direction;
            const auto normal = hit_object->get_normal_at(intersection_point);
            return (normal + 1.f) / 2.f;
        }
        else
        {
            glm::vec3 unit_direction = glm::normalize(ray.direction);
            auto a = 0.5f * (unit_direction.y + 1.0f);
            const auto default_color = (1.0f - a) * glm::vec3(1.0f, 1.0f, 1.0f)
                + a * glm::vec3(0.5f, 0.7f, 1.0f);

            return default_color;
        }
    }
} // namespace yart
