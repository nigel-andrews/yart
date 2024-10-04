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

                // TODO: depth test
                for (const auto& object : objects)
                {
                    if (object->intersect(ray))
                    {
                        render_function_(
                            glm::vec3{ i / float(width_ - 1) * 255.999,
                                       j / float(height_ - 1) * 255.999, 0.f },
                            i, j);
                    }
                    else
                    {
                        render_function_({}, i, j);
                    }
                }
            }
        }
    }
} // namespace yart
