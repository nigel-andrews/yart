add_library(renderer STATIC renderer.cpp sampler.cpp window.cpp)

set_target_properties(renderer PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)

target_link_libraries(renderer PRIVATE compile_options glm::glm scene)
