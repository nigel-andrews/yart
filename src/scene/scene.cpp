#include "scene.h"

#include <algorithm>
#include <glm/geometric.hpp>

#include "utils/misc.h"
#include "utils/view_ptr.h"

namespace
{
    constexpr glm::vec3 ambient_light{ 0.1f };
    constexpr auto MAX_DEPTH = 3;

    glm::vec3 reflect(const glm::vec3& incident, const glm::vec3& normal)
    {
        return incident - 2.f * glm::dot(normal, incident) * normal;
    }
} // namespace

glm::vec3 scene::compute_color(const object& object, const ray& ray,
                               float t) const
{
    // TODO: gamma correction

    const auto light_direction =
        glm::normalize(light_source_.position - object.position);
    const auto normal = object.get_normal_at(ray[t]);
    const auto incident_angle = glm::dot(normal, light_direction);

    const auto view_direction =
        glm::normalize(camera_.position_get() - object.position);
    const auto reflection = reflect(-light_direction, normal);
    float spec =
        std::pow(std::max(glm::dot(view_direction, reflection), 0.f), 32) / 2.f;

    return (ambient_light + object.material.albedo / static_cast<float>(M_PI)
            + spec)
        * light_source_.colour * std::clamp(light_source_.intensity, 0.f, 1.f)
        * std::max(incident_angle, 0.f);
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

        if (*root < closest_root)
        {
            closest_root = *root;
            hit_object = object;
        }
    }

    if (closest_root != std::numeric_limits<float>::max())
        return compute_color(*hit_object, ray, closest_root);
    else
    {
        auto t = 0.5f * (ray.direction.y + 1.f);
        return utils::lerp(glm::vec3{ 1.f }, glm::vec3{ 0.5f, 0.7f, 1.0f }, t);
    }
}
