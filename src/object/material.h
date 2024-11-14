#pragma once

// Material interface
#include "glm/vec3.hpp"

// TODO: turn this into a class
struct material
{
    // TODO: use a variant and visit to correct material since both are
    //       orthogonal to eachother
    glm::vec3 albedo{};

    glm::vec3 emit_color{};
    float light_intensity = 0.f;
};
