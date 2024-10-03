#pragma once

#include "scene/scene.h"
#include "render_functions.h"

namespace yart
{
    // This class abstracts the ray casting done by the camera
    // The render function is determined by the RenderFunction template
    // at compile time.
    template <typename F = render_functions::ppm_renderer>
    class renderer
    {
        public:
            template <typename... args>
            renderer(int width, int height, args... params)
                : render_function_{params...}
                , width_{width}
                , height_{height}
        {}

            int width_get() const { return width_;}
            int height_get() const {return height_;}

            void render_scene(const scene& /*scene*/)
            {
                if constexpr (render_functions::needs_setup<F>::value)
                {
                    render_function_.setup(width_, height_);
                }

                for (auto j = 0; j < height_; ++j)
                {
                    for (auto i = 0; i < width_; ++i)
                    {
                        render_function_(glm::vec3{}, i, j);
                    }
                }
            }

        private:
            F render_function_;
            int width_;
            int height_;
    };
};
