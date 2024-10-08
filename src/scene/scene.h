#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "object/object.h"

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

        void add_object(std::unique_ptr<object> object)
        {
            objects_.push_back(std::move(object));
        }

        template <class Self>
        auto&& camera_get(this Self&& self)
        {
            return std::forward<Self>(self).camera_;
        }

        template <class Self>
        auto&& objects_get(this Self&& self)
        {
            return std::forward<Self>(self).objects_;
        }

    private:
        camera camera_;
        std::vector<std::unique_ptr<object>> objects_;
    };
} // namespace yart
