#pragma once

#include "render_functions.h"
#include "scene/scene.h"

namespace yart
{
    // TODO: Concept constraint
    // This class abstracts the ray casting done by the camera
    // The render function is determined by the RenderFunction template
    // at compile time.
    template <typename F = render_functions::ppm_renderer>
    class renderer
    {
    public:
        using render_function_t = F;

        template <typename... args>
        renderer(int width, int height, args... params)
            : render_function_{ params... }
            , width_{ width }
            , height_{ height }
        {}

        int width_get() const
        {
            return width_;
        }
        int height_get() const
        {
            return height_;
        }

        void render_scene(const scene& /*scene*/);

    private:
        F render_function_;
        int width_;
        int height_;
    };
}; // namespace yart

#include "renderer.hxx"
