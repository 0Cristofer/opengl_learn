cmake_minimum_required(VERSION 3.17)
project(opengl_learn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(DEPS_DIRECTORY ${CMAKE_SOURCE_DIR}/deps)
set(GLEW_DIRECTORY ${DEPS_DIRECTORY}/GLEW)
set(GLFW_DIRECTORY ${DEPS_DIRECTORY}/GLFW)

add_subdirectory(opengl_basic)
add_subdirectory(opengl_abst)
add_subdirectory(opengl_testable)
