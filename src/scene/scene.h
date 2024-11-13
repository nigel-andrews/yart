#pragma once

#include <functional>
#include <memory>

#include "camera.h"
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

    template <typename Callable>
    void environment_lighting_set(Callable&& callable)
    {
        environment_lighting_ = std::forward<Callable>(callable);
    }

private:
    glm::vec3 compute_color(const object& object, const ray& ray, float t,
                            int depth) const;

    camera camera_;
    // FIXME: handle default lighting better
    std::function<glm::vec3(const ray& r)> environment_lighting_ =
        [](const ray&) { return glm::vec3{}; };
    std::vector<std::unique_ptr<object>> objects_;
};
