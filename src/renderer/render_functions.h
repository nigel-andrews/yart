#pragma once

#include <glm/gtx/string_cast.hpp>
#include <glm/vec3.hpp>
#include <format>
#include <iostream>
#include <type_traits>

namespace yart::render_functions
{
    struct ppm_renderer
    {
        void setup(int width, int height)
        {
            std::cout << std::format("P3\n{} {}\n255\n", width, height);
        }

        void operator()(const glm::vec3& colour, int, int)
        {
            // FIXME: colour remapping
            // FIXME: the stream should be part of the state of the renderer
            std::cout
                << static_cast<int>(colour.r) << ' '
                << static_cast<int>(colour.g) << ' '
                << static_cast<int>(colour.b) << '\n';
        }
    };

    template <typename T>
    struct needs_setup : std::false_type
    {};

    template<>
    struct needs_setup<ppm_renderer> : std::true_type{};

    static_assert(std::is_function_v<ppm_renderer()>);
} // namespace yart::render_function
