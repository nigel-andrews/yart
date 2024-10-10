#include "scene.h"

#include <glm/geometric.hpp>

#include "utils/view_ptr.h"

namespace yart
{
    namespace
    {
        glm::vec3 compute_color(const object& object, const ray& /*ray*/,
                                float /*closest_root*/)
        {
            return object.material.albedo;
        }
    } // namespace

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
