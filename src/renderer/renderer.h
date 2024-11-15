#pragma once

#include "renderer/bsdf.h"
#include "renderer/sampler.h"
#include "scene/scene.h"

class renderer
{
public:
    constexpr renderer(int width, int height)
        : width_{ width }
        , height_{ height }
    {
        if (width_ < 1 || height_ < 1)
        {
            throw std::invalid_argument(
                "Screen sizes must be greater than 0 !");
        }

        framebuffer_.resize(width * height);
    }

    constexpr int width_get() const
    {
        return width_;
    }
    constexpr int height_get() const
    {
        return height_;
    }

    constexpr float aspect_ratio() const
    {
        return static_cast<float>(width_) / static_cast<float>(height_);
    }

    void set_pixel(const glm::vec3& colour, int i, int j)
    {
        // GCC does not support mdspans
        framebuffer_[j * width_ + i] = colour;
    }

    const glm::vec3& get_pixel(int i, int j)
    {
        // GCC does not support mdspans
        return framebuffer_[j * width_ + i];
    }

    void render_scene(const scene& scene, const sampler& sampler,
                      const bsdf& bsdf);

    template <typename RenderFunction>
    void display(RenderFunction&& func);

private:
    glm::vec2 ndc_coords(int i, int j)
    {
        return { ((2.f * static_cast<float>(i) / width_) - 1.f)
                     * aspect_ratio(),
                 1.f - 2.f * (static_cast<float>(j) / height_) };
    }

private:
    int width_;
    int height_;
    std::vector<glm::vec3> framebuffer_;
};

#include "renderer.hxx"
