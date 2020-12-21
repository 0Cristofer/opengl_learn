cmake_minimum_required(VERSION 3.17)
project(opengl_basic)

find_package(OpenGL REQUIRED)

add_executable(opengl_basic src/main.cpp)

target_compile_definitions(opengl_basic PRIVATE GLEW_STATIC)
target_include_directories(opengl_basic PRIVATE ${GLEW_DIRECTORY}/include)
target_link_libraries(opengl_basic ${GLEW_DIRECTORY}/lib/Release/Win32/glew32s.lib)

target_include_directories(opengl_basic PRIVATE ${GLFW_DIRECTORY}/include)
target_link_libraries(opengl_basic ${GLFW_DIRECTORY}/lib-vc2019/glfw3.lib)
target_link_libraries(opengl_basic OpenGL::GL)
