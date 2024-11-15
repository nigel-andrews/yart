#pragma once

#include <functional>
#include <glm/vec3.hpp>

#include "object/object.h"
#include "utils/view_ptr.h"

class bsdf
{
public:
    // NOTE: Despite the same prototypes, lambdas are considered as unique types
    // so in order to build a bsdf from lambdas, two types are needed in this
    // template.
    template <typename CallableDiffuse, typename CallableSpecular>
    constexpr bsdf(CallableDiffuse&& diffuse, CallableSpecular&& specular)
        : diffuse_(std::forward<CallableDiffuse>(diffuse))
        , specular_(std::forward<CallableSpecular>(specular))
    {}

    glm::vec3 evaluate_at(utils::view_ptr<object> object,
                          const glm::vec3& point,
                          const glm::vec3& light_direction,
                          const glm::vec3& view_direction) const
    {
        // TODO: weighted by kD and kS
        return diffuse_(object, point, light_direction, view_direction)
            + specular_(object, point, light_direction, view_direction);
    }

private:
    std::function<glm::vec3(utils::view_ptr<object>, const glm::vec3&,
                            const glm::vec3&, const glm::vec3&)>
        diffuse_;
    std::function<glm::vec3(utils::view_ptr<object>, const glm::vec3&,
                            const glm::vec3&, const glm::vec3&)>
        specular_;
};
