#pragma once

#include <algorithm>
#include <format>
#include <glm/vec3.hpp>
#include <iostream>
#include <type_traits>

#include "window.h"

namespace render_functions
{
    struct ppm3_renderer
    {
        void setup(int width, int height)
        {
            std::cout << std::format("P3\n{} {}\n255\n", width, height);
        }

        void operator()(const glm::vec3& colour, int, int)
        {
            // FIXME: the stream should be part of the state of the renderer
            std::cout
                << static_cast<int>(std::clamp(colour.r * 255.999f, 0.f, 255.f))
                << ' '
                << static_cast<int>(std::clamp(colour.g * 255.999f, 0.f, 255.f))
                << ' '
                << static_cast<int>(std::clamp(colour.b * 255.999f, 0.f, 255.f))
                << '\n';
        }
    };

    struct sdl2_renderer
    {
        void operator()(const glm::vec3& colour, int i, int j)
        {
            Uint8 r =
                static_cast<Uint8>(std::clamp(colour.r * 255.0f, 0.0f, 255.0f));
            Uint8 g =
                static_cast<Uint8>(std::clamp(colour.g * 255.0f, 0.0f, 255.0f));
            Uint8 b =
                static_cast<Uint8>(std::clamp(colour.b * 255.0f, 0.0f, 255.0f));

            win.draw_point(r << 16 | g << 8 | b, i, j);
        }

        window& win;
    };

    template <typename T>
    struct needs_setup : std::false_type
    {};

    template <>
    struct needs_setup<ppm3_renderer> : std::true_type
    {};

    static_assert(std::is_function_v<ppm3_renderer()>);
    static_assert(std::is_function_v<sdl2_renderer()>);
} // namespace render_functions
