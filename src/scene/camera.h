#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>

namespace yart
{
    // Camera space is normalized to [-1, 1].
    // Here, it is the renderer's job to abstract the screen size rendered and
    // the camera only has to handle the normalized space
    class camera
    {
    public:
        constexpr camera(float near_plane = 1.f, float fov = 90.f)
            : near_plane_(near_plane)
            , fov_(fov)
        {}

        void look_at(const glm::vec3& position, const glm::vec3& up,
                     const glm::vec3& target);

        // Screen must be normalized
        glm::vec3 compute_ray_direction(const glm::vec2& screen_pos) const;

        template <class Self>
        auto&& position_get(this Self&& self)
        {
            return std::forward<Self>(self).position_;
        }

    private:
        glm::vec3 position_;
        glm::vec3 target_;
        glm::vec3 up_;
        glm::vec3 right_;
        float near_plane_;
        float fov_;
    };
} // namespace yart
