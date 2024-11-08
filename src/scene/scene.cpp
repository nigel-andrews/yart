#include "scene.h"

#include <glm/geometric.hpp>

#include "object/ray.h"
#include "utils/misc.h"
#include "utils/view_ptr.h"

namespace
{
    constexpr auto MAX_DEPTH = 3;

    // // From
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
    // glm::vec3 reflect(const glm::vec3& incident, const glm::vec3& normal)
    // {
    //     return incident - 2.f * glm::dot(normal, incident) * normal;
    // }
} // namespace

// FIXME: overlapping shadows should contribute to stronger shading
bool scene::is_obstructed(ray r, utils::view_ptr<object> current) const
{
    for (const auto& object : objects_)
    {
        if (current == object)
            continue;

        if (object->intersect(r))
            return true;
    }

    return false;
}

// TODO: gamma correction
glm::vec3 scene::cast_ray(const ray& r, int depth) const
{
    if (depth >= MAX_DEPTH)
        return {};

    float closest_root{ std::numeric_limits<float>::max() };
    utils::view_ptr<object> hit_object;

    for (const auto& object : objects_)
    {
        const auto root = object->intersect(r);

        if (!root)
            continue;

        if (*root < closest_root)
        {
            closest_root = *root;
            hit_object = object;
        }
    }

    if (closest_root == std::numeric_limits<float>::max())
    {
        auto t = 0.5f * (r.direction.y + 1.f);
        return utils::lerp(glm::vec3{ 1.f }, glm::vec3{ 0.5f, 0.7f, 1.0f }, t);
    }

    const auto intersection_point = r[closest_root];
    const auto normal = hit_object->get_normal_at(intersection_point);

    return utils::clamp_vec3(
        0.5f
        * cast_ray(
            { intersection_point, ray::hemisphere_ray_direction(normal) },
            depth + 1));
}
