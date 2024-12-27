#pragma once

#include <cmath>

#include "render_functions.h"
#include "renderer.h"

// FIXME: This is incompatible with window based display (vs rendering to an
// output image)
template <typename RenderFunction>
void renderer::display(RenderFunction&& func)
{
    if constexpr (render_functions::needs_setup<RenderFunction>::value)
        func.setup(width_, height_);

    for (auto j = 0; j < height_; ++j)
        for (auto i = 0; i < width_; ++i)
            func(get_pixel(i, j), i, j);
}
