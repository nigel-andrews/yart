#pragma once

#include <algorithm>
#include <glm/vec3.hpp>
#include <random>

namespace utils
{
    template <typename T>
    constexpr T lerp(T start, T end, float t)
    {
        return (1.f - t) * start + t * end;
    }

    // NOTE: nclamp == normal clamp
    template <typename T>
    constexpr T nclamp(T value)
    {
        return std::clamp(value, (T)0, (T)1);
    }

    constexpr void clamp_vec3(glm::vec3& vec)
    {
        vec.r = nclamp(vec.r);
        vec.g = nclamp(vec.g);
        vec.b = nclamp(vec.b);
    }

    constexpr glm::vec3 clamp_vec3(glm::vec3 vec)
    {
        vec.r = nclamp(vec.r);
        vec.g = nclamp(vec.g);
        vec.b = nclamp(vec.b);

        return vec;
    }

    inline float randf()
    {
        static std::uniform_real_distribution<float> distribution(-1.f, 1.f);
        static std::mt19937 generator;

        return distribution(generator);
    }
} // namespace utils
