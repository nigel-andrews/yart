#pragma once

#include "traits.h"

namespace utils
{
    template <typename T>
    class singleton
        : non_copyable
        , non_movable
    {
    protected:
        static T& get_instance()
        {
            static T instance;
            return instance;
        }

        singleton() = default;
        ~singleton() = default;
    };
} // namespace utils
