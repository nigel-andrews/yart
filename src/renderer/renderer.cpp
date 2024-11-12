#include "renderer.h"

#include <cmath>

#include "utils/misc.h"

namespace
{
#ifdef DEBUG
    constexpr auto SAMPLES = 5;
#else
    constexpr auto SAMPLES = 50;
#endif
} // namespace

void renderer::render_scene(const scene& scene, const sampler& sampler)
{
    const auto& camera = scene.camera_get();
    ray r{ camera.position_get(), {} };

    for (auto j = 0; j < height_; ++j)
    {
        for (auto i = 0; i < width_; ++i)
        {
            glm::vec3 colour{};

            for (auto s = 0; s < SAMPLES; ++s)
            {
                auto sample = sampler.sample2D({ i, j });
                r.direction = camera.compute_ray_direction(
                    ndc_coords(sample.x, sample.y));
                colour += scene.cast_ray(r);
            }

            set_pixel(colour / static_cast<float>(SAMPLES), i, j);
        }
    }
}
