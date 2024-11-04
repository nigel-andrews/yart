#pragma once

#include <format>
#include <glm/gtx/string_cast.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <type_traits>

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
            std::cout << static_cast<int>(colour.r * 255.999) << ' '
                      << static_cast<int>(colour.g * 255.999) << ' '
                      << static_cast<int>(colour.b * 255.999) << '\n';
        }
    };

    template <typename T>
    struct needs_setup : std::false_type
    {};

    template <>
    struct needs_setup<ppm3_renderer> : std::true_type
    {};

    static_assert(std::is_function_v<ppm3_renderer()>);
} // namespace render_functions
