#include "renderer.h"

#include <cmath>

void renderer::render_scene(const scene& scene)
{
    const auto& camera = scene.camera_get();
    ray ray{ camera.position_get(), {} };
    for (auto j = 0; j < height_; ++j)
    {
        for (auto i = 0; i < width_; ++i)
        {
            // TODO: anti aliasing (offset i and j a bit and generate a ray)
            //       i and j represent the center of the pixel "square"
            auto ndc = ndc_coords(i, j);
            ndc *= std::tan(camera.fov_get() / 2.f * M_PI / 180.f);
            ray.direction = camera.compute_ray_direction(ndc);
            set_pixel(scene.cast_ray(ray), i, j);
        }
    }
}
