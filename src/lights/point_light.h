#pragma once

#include <glm/vec3.hpp>

struct point_light
{
    glm::vec3 position;
    glm::vec3 colour;
    float intensity;
};
