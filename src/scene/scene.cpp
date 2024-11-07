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

// FIXME: overlapping shadows should contribute to stronger shading
bool scene::is_obstructed(ray r, utils::view_ptr<const object> current) const
{
    for (const auto& object : objects_)
    {
        if (current == object.get())
            continue;

        if (object->intersect(r))
            return true;
    }

    return false;
}

// TODO: gamma correction
glm::vec3 scene::compute_color(const object& object, const ray& ray, float t,
                               int depth) const
{
    const auto light_direction =
        glm::normalize(light_source_.position - object.position);

    if (is_obstructed({ ray[t], light_direction }, &object))
        return object.material.albedo / 2.f;

    const auto normal = object.get_normal_at(ray[t]);
    const auto incident_angle = glm::dot(normal, light_direction);

    return object.material.albedo * incident_angle;
}

// TODO: anti aliasing
glm::vec3 scene::cast_ray(const ray& ray, int depth) const
{
    if (depth >= MAX_DEPTH)
        return {};

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
        return utils::clamp_vec3(
            compute_color(*hit_object, ray, closest_root, depth));
    else
    {
        auto t = 0.5f * (ray.direction.y + 1.f);
        return utils::lerp(glm::vec3{ 1.f }, glm::vec3{ 0.5f, 0.7f, 1.0f }, t);
    }
}
