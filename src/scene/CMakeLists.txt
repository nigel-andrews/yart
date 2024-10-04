add_library(scene STATIC camera.cpp)

set_target_properties(scene PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)

target_link_libraries(scene PRIVATE compile_options glm::glm)
