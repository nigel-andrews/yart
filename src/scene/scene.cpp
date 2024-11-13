#include "scene.h"

#include <glm/geometric.hpp>

#include "object/ray.h"
#include "utils/misc.h"
#include "utils/view_ptr.h"

namespace
{
    constexpr auto MAX_DEPTH = 3;
} // namespace

// TODO: gamma correction
glm::vec3 scene::cast_ray(const ray& r, int depth) const
{
    if (depth == MAX_DEPTH)
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
        return environment_lighting_(r);

    const auto intersection_point = r[closest_root];
    // TODO: use normal + random hemisphere_ray_direction trick for better
    // distribution
    const auto normal = hit_object->get_normal_at(intersection_point);
    // Rendering equation -> Le + S brdf * Li * n.l dl
    // S -> random hemisphere_ray_directions

    return utils::clamp_vec3(cast_ray(
        { intersection_point,
          glm::normalize(normal + ray::hemisphere_ray_direction(normal)) },
        depth + 1));
}
