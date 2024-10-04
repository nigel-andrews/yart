#include "camera.h"

#include <glm/geometric.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace yart
{
    void camera::look_at(const glm::vec3& position, const glm::vec3& up,
                         const glm::vec3& target)
    {
        position_ = position;
        target_ = target;

        const auto view_direction = glm::normalize(target - position);
        right_ = glm::normalize(glm::cross(glm::normalize(up), view_direction));
        up_ = glm::normalize(glm::cross(view_direction, right_));
    }

    glm::vec3 camera::compute_ray_direction(const glm::vec2& screen_pos) const
    {
        // Finding the point on the screen
        return glm::normalize(glm::vec3{ 0.f, 0.f, -near_plane_ }
                              - right_ * screen_pos.x + up_ * screen_pos.y);
    }
} // namespace yart
