#pragma once

#include <memory>

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

        constexpr operator bool()
        {
            return ptr_ != nullptr;
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
