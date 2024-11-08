#include "renderer.h"

#include <cmath>

#include "utils/misc.h"

namespace
{
    constexpr auto SAMPLES = 10;
} // namespace

glm::vec3 renderer::sample_pixels(const scene& scene, const camera& camera,
                                  int i, int j)
{
    glm::vec3 colour{};

    ray r{ camera.position_get(), {} };
    for (auto _ = 0; _ < SAMPLES; ++_)
    {
        glm::vec2 offsets{ utils::randf(), utils::randf() };
        offsets += 1.f;
        offsets /= 2.f;
        offsets -= 0.5f;
        const auto ndc = ndc_coords(i + offsets.x, j + offsets.y);
        const auto screen_pos =
            ndc * std::tanf(camera.fov_get() / 2.f * M_PI / 180.f);
        r.direction = camera.compute_ray_direction(screen_pos);
        colour += scene.cast_ray(r);
    }

    return colour / static_cast<float>(SAMPLES);
}

void renderer::render_scene(const scene& scene)
{
    const auto& camera = scene.camera_get();
    for (auto j = 0; j < height_; ++j)
    {
        for (auto i = 0; i < width_; ++i)
            set_pixel(sample_pixels(scene, camera, i, j), i, j);
    }
}
