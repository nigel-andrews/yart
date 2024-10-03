add_library(object STATIC sphere.cpp)

set_target_properties(object PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)

target_link_libraries(object PRIVATE compile_options glm::glm)
