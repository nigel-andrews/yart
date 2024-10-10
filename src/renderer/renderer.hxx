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
                auto ndc = ndc_coords(i, j);
                ndc *= std::tan(camera.fov_get() / 2.f * M_PI / 180.f);
                ray.direction = camera.compute_ray_direction(ndc);
                render_function_(scene.cast_ray(ray), i, j);
            }
        }
    }
} // namespace yart
