#pragma once

#include "traits.h"

namespace yart::utils
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

    private:
        singleton() = default;
        ~singleton() = default;
    };
} // namespace yart::utils
