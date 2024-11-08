#pragma once

namespace utils
{
    // NOTE: see if negative powers are interesting to have
    template <unsigned long N, typename T>
    constexpr T pow(T x)
    {
        if constexpr (N == 0)
            return (T)1;

        if constexpr (N == 1)
            return x;

        if constexpr (N % 2 == 0)
            return pow<N / 2>(x * x);
        else
            return x * pow<(N - 1) / 2>(x * x);
    }
} // namespace utils
