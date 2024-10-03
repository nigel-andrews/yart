#pragma once

#include <memory>
#include <vector>

#include "object/object.h"

namespace yart
{
    class scene
    {
    public:
        void add_object(object* object)
        {
            objects_.emplace_back(object);
        }

        void add_object(std::unique_ptr<object> object)
        {
            objects_.push_back(std::move(object));
        }

    private:
        std::vector<std::unique_ptr<object>> objects_;
    };
} // namespace yart
