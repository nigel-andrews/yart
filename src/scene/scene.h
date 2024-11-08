#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "lights/point_light.h"
#include "object/object.h"
#include "utils/view_ptr.h"

class scene
{
public:
    glm::vec3 cast_ray(const ray& ray, int depth = 0) const;

    void add_object(object* object)
    {
        objects_.emplace_back(object);
    }

    utils::view_ptr<object> add_object(std::unique_ptr<object> object)
    {
        objects_.push_back(std::move(object));
        return objects_.back();
    }

    void light_source_set(const glm::vec3& position, float intensity = 1.f,
                          const glm::vec3& colour = glm::vec3{ 1.f })
    {
        light_source_ = point_light{ position, colour, intensity };
    }

    template <class Self>
    auto& camera_get(this Self&& self)
    {
        return std::forward<Self>(self).camera_;
    }

    template <class Self>
    auto& objects_get(this Self&& self)
    {
        return std::forward<Self>(self).objects_;
    }

private:
    bool is_obstructed(ray r, utils::view_ptr<object> current) const;
    glm::vec3 compute_color(const object& object, const ray& ray, float t,
                            int depth) const;

    camera camera_;
    // TODO: Multiple lights
    point_light light_source_;
    std::vector<std::unique_ptr<object>> objects_;
};
