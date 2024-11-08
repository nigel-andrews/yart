cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(yart)

include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1)

FetchContent_MakeAvailable(glm)

add_library(compile_options INTERFACE)

target_compile_options(
  compile_options
  INTERFACE "-Wall"
            "-Wextra"
            "-std=c++23"
            $<$<CONFIG:Release>:-O3>
            $<$<CONFIG:Release>:-Werror>
            $<$<CONFIG:Debug>:-O0>
            $<$<CONFIG:Debug>:-fno-inline>
            $<$<CONFIG:Debug>:-g3>
            $<$<CONFIG:Debug>:-fsanitize=address>)

target_link_options(compile_options INTERFACE
                    $<$<CONFIG:Debug>:-fsanitize=address>)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(tests)
add_subdirectory(src)

add_executable(yart src/main.cpp)

set_target_properties(yart PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)

target_include_directories(compile_options INTERFACE ${SRC_DIR})

target_compile_definitions(compile_options INTERFACE GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(yart PRIVATE compile_options glm::glm scene object
                                   renderer)
