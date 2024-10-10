#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "lights/point_light.h"
#include "object/object.h"
#include "utils/view_ptr.h"

namespace yart
{
    class scene
    {
    public:
        glm::vec3 cast_ray(const ray& ray) const;

        void add_object(object* object)
        {
            objects_.emplace_back(object);
        }

        utils::view_ptr<object> add_object(std::unique_ptr<object> object)
        {
            objects_.push_back(std::move(object));
            return objects_.back();
        }

        void light_source_set(const glm::vec3& position,
                              const glm::vec3& colour = glm::vec3{ 1.f })
        {
            light_source_ = lights::point_light{ position, colour };
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
        camera camera_;
        lights::point_light light_source_;
        std::vector<std::unique_ptr<object>> objects_;
    };
} // namespace yart
