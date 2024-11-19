#include "renderer.h"

#include <cmath>

#include "glm/exponential.hpp"

namespace
{
#ifdef DEBUG
    constexpr auto SAMPLES = 3;
#else
    constexpr auto SAMPLES = 5;
#endif

    constexpr float gamma = 2.2f;

    glm::vec3 gamma_correction(const glm::vec3& linear_colour)
    {
        return glm::pow(linear_colour, glm::vec3{ 1.f / gamma });
    }
} // namespace

void renderer::render_scene(const scene& scene, const sampler& sampler,
                            const bsdf& bsdf)
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
                colour += scene.cast_ray(r, bsdf);
            }

            set_pixel(gamma_correction(colour / static_cast<float>(SAMPLES)), i,
                      j);
        }
    }
}
