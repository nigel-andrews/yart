#pragma once

#include <memory>

#include "utils/traits.h"

namespace utils
{
    // Type erased non-owning ptr
    // TODO: move to another repo
    template <class T>
    class view_ptr
    {
    public:
        constexpr view_ptr() = default;

        constexpr view_ptr(T* ptr)
            : ptr_(ptr)
        {}

        // Never owns smart pointers
        constexpr view_ptr(const std::unique_ptr<T>& ptr)
            : ptr_(ptr.get())
        {}
        constexpr view_ptr(const std::shared_ptr<T>& ptr)
            : ptr_(ptr.get())
        {}

        constexpr operator bool() const
        {
            return ptr_ != nullptr;
        }

        constexpr bool operator==(const view_ptr& rhs) const
        {
            return ptr_ == rhs.ptr_;
        }

        friend constexpr bool operator==(const view_ptr& lhs,
                                         const SmartPointer auto&& rhs)
        {
            return lhs.ptr_ == rhs.get();
        }

        constexpr T& operator*() const
        {
            return *ptr_;
        }

        constexpr T* operator->() const noexcept
        {
            return ptr_;
        }

    private:
        T* ptr_;
    };
} // namespace utils
