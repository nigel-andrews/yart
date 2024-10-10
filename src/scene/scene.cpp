#include "scene.h"

#include <glm/geometric.hpp>

#include "utils/view_ptr.h"

namespace yart
{
    glm::vec3 scene::compute_color(const object& object, const ray& ray,
                                   float t) const
    {
        // TODO: gamma correction
        const auto light_direction =
            glm::normalize(light_source_.position - object.position);
        const auto incident_angle =
            glm::dot(object.get_normal_at(ray[t]), light_direction);

        return (object.material.albedo / static_cast<float>(M_PI))
            * light_source_.colour * std::max(incident_angle, 0.f);
    }

    glm::vec3 scene::cast_ray(const ray& ray) const
    {
        float closest_root{ std::numeric_limits<float>::max() };
        utils::view_ptr<object> hit_object;

        for (const auto& object : objects_)
        {
            const auto root = object->intersect(ray);

            if (!root)
                continue;

            closest_root = std::min(*root, closest_root);
            hit_object = object;
        }

        if (closest_root != std::numeric_limits<float>::max())
        {
            return compute_color(*hit_object, ray, closest_root);
        }
        else
        {
            return {};
        }
    }
} // namespace yart
