#include "scene.h"

#include <glm/geometric.hpp>
#include <glm/gtc/random.hpp>

#include "object/ray.h"
#include "utils/misc.h"
#include "utils/view_ptr.h"

namespace
{
#ifdef DEBUG
    constexpr auto MAX_DEPTH = 3;
#else
    constexpr auto MAX_DEPTH = 50;
#endif /* DEBUG */
} // namespace

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
    const auto normal = hit_object->get_normal_at(intersection_point);

    const auto emissive =
        hit_object->mat.emit_color * hit_object->mat.light_intensity;

    // TODO: BxDF and integral
    const auto irradiance =
        cast_ray({ intersection_point,
                   glm::normalize(normal + glm::sphericalRand(1.f)) },
                 depth + 1);

    return utils::clamp_vec3(emissive + irradiance);
}
