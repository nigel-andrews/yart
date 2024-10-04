#pragma once

#include "render_functions.h"
#include "scene/scene.h"

namespace yart
{
    // TODO: Concept constraint
    // This class abstracts the ray casting done by the camera
    // The render function is determined by the RenderFunction template
    // at compile time.
    template <typename F = render_functions::ppm3_renderer>
    class renderer
    {
    public:
        using render_function_t = F;

        template <typename... args>
        constexpr renderer(int width, int height, args... params)
            : render_function_{ params... }
            , width_{ width }
            , height_{ height }
        {}

        constexpr int width_get() const
        {
            return width_;
        }
        constexpr int height_get() const
        {
            return height_;
        }

        constexpr int aspect_ratio() const
        {
            return static_cast<float>(width_) / static_cast<float>(height_);
        }

        void render_scene(const scene& scene);

    private:
        glm::vec2 ndc_coords(int i, int j)
        {
            return { ((2.f * (static_cast<float>(i) + 0.5f) / width_) - 1.f)
                         * aspect_ratio(),
                     1.f - 2.f * ((static_cast<float>(j) + 0.5f) / height_) };
        }

    private:
        F render_function_;
        int width_;
        int height_;
    };
}; // namespace yart

#include "renderer.hxx"
