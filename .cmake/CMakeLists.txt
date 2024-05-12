cmake_minimum_required(VERSION 3.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../targets)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_BINARY_DIR}/../compile_commands.json
    COPYONLY
)

project(RotatingCube)
add_executable(cube "../src/cube.cpp")
target_link_libraries(cube raylib)

project(RotatingSphere)
add_executable(sphere "../src/sphere.cpp")
target_link_libraries(sphere raylib)
