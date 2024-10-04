#pragma once

#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "singleton.h"
#include "traits.h"

namespace yart::utils
{
    class logger : singleton<logger>
    {
    public:
        static logger& get_logger_instance()
        {
            return get_instance();
        }

        // Become no-op if debug is disabled in case I don't want to remove my
        // logs
        template <typename T>
        logger& operator<<(T&& value)
        {
#ifndef NDEBUG
            if constexpr (is_glm_vec<std::decay_t<T>>::value)
            {
                std::clog << glm::to_string(std::forward<T>(value));
            }
            else
            {
                std::clog << std::forward<T>(value);
            }
#endif
            return *this;
        }

    private:
        using char_type = std::ostream::char_type;
        using traits_type = std::ostream::traits_type;

        using stream_func_t = std::basic_ostream<
            char_type,
            traits_type>& (*)(std::basic_ostream<char_type, traits_type>&);

    public:
        logger& operator<<(stream_func_t func)
        {
#ifndef NDEBUG
            std::clog << func;
#endif
            return *this;
        }

    private:
        friend singleton;
    };

    inline logger& log()
    {
        return logger::get_logger_instance();
    }
} // namespace yart::utils
