#pragma once

#include <concepts>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <type_traits>

namespace utils::inline traits
{
    struct non_copyable
    {
        non_copyable() = default;
        non_copyable(const non_copyable&) = delete;
        non_copyable& operator=(const non_copyable&) = delete;
    };

    struct non_movable
    {
        non_movable() = default;
        non_movable(const non_movable&) = delete;
        non_movable& operator=(const non_movable&) = delete;
    };

    template <typename Ptr>
    concept SmartPointer = requires(Ptr ptr) {
        typename Ptr::element_type;
        {
            ptr.get()
        } -> std::convertible_to<typename Ptr::element_type*>;
        {
            ptr.operator->()
        } -> std::convertible_to<typename Ptr::element_type*>;
        {
            *ptr
        } -> std::convertible_to<typename Ptr::element_type>;
        {
            static_cast<bool>(ptr)
        };
    };

    template <typename T>
    struct is_glm_vec : std::false_type
    {};

    template <>
    struct is_glm_vec<glm::vec2> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::vec3> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::vec4> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::ivec2> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::ivec3> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::ivec4> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::dvec2> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::dvec3> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::dvec4> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::uvec2> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::uvec3> : std::true_type
    {};

    template <>
    struct is_glm_vec<glm::uvec4> : std::true_type
    {};

} // namespace utils::inline traits
