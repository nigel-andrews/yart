#pragma once

#include "renderer.h"

namespace yart
{
    template <typename F>
    void renderer<F>::render_scene(const scene& scene)
    {
        if constexpr (render_functions::needs_setup<F>::value)
        {
            render_function_.setup(width_, height_);
        }

        const auto& camera = scene.camera_get();
        ray ray{ camera.position_get(), {} };
        for (auto j = 0; j < height_; ++j)
        {
            for (auto i = 0; i < width_; ++i)
            {
                const auto ndc = ndc_coords(i, j);
                ray.direction = camera.compute_ray_direction(ndc);
                const auto& objects = scene.objects_get();
                glm::vec3 unit_direction = glm::normalize(ray.direction);
                auto a = 0.5f * (unit_direction.y + 1.0f);
                const auto default_color =
                    (1.0f - a) * glm::vec3(1.0f, 1.0f, 1.0f)
                    + a * glm::vec3(0.5f, 0.7f, 1.0f);

                // TODO: depth test
                for (const auto& object : objects)
                {
                    render_function_(
                        object->intersect(ray).value_or(default_color), i, j);
                }
            }
        }
    }
} // namespace yart
