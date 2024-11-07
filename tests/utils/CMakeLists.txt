add_executable(utils utils.cpp)

target_include_directories(utils PRIVATE ../../src/)
target_link_libraries(utils PRIVATE compile_options glm::glm
                                    Catch2::Catch2WithMain)
