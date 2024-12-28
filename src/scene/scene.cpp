#include "scene.h"

#include <glm/geometric.hpp>
#include <glm/gtc/random.hpp>

#include "utils/misc.h"

namespace
{
#ifdef DEBUG
    constexpr auto MAX_DEPTH = 2;
    constexpr auto TRACES = 2;
#else
    constexpr auto MAX_DEPTH = 3;
    constexpr auto TRACES = 3;
#endif /* DEBUG */

    // FIXME: emissive should be an object member function
    inline glm::vec3 emissive(const material& material)
    {
        return material.light_intensity * material.emit_color;
    }
} // namespace

glm::vec3 scene::cast_ray(const ray& r, const bsdf& bsdf, int depth) const
{
    // NOTE: enough rays have been computed
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

    // TODO: Importance sampling
    glm::vec3 irradiance{};
    for (auto i = 0; i < TRACES; ++i)
    {
        const auto w_i = glm::normalize(normal + glm::sphericalRand(1.f));
        irradiance +=
            bsdf.evaluate_at(hit_object, intersection_point, w_i, r.direction)
            * cast_ray({ intersection_point, w_i }, bsdf, depth + 1);
    }

    return emissive(hit_object->mat) + irradiance;
}
