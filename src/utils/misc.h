#pragma once

namespace yart::utils
{
    template <typename T>
    constexpr T lerp(T start, T end, float t)
    {
        return (1.f - t) * start + t * end;
    }
} // namespace yart::utils
