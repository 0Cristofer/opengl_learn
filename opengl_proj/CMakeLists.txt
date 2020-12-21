cmake_minimum_required(VERSION 3.17)
project(opengl_proj)

find_package(OpenGL REQUIRED)

add_executable(opengl_proj src/main.cpp)

target_compile_definitions(opengl_proj PRIVATE GLEW_STATIC)
target_include_directories(opengl_proj PRIVATE ${GLEW_DIRECTORY}/include)
target_link_libraries(opengl_proj ${GLEW_DIRECTORY}/lib/Release/Win32/glew32s.lib)

target_include_directories(opengl_proj PRIVATE ${GLFW_DIRECTORY}/include)
target_link_libraries(opengl_proj ${GLFW_DIRECTORY}/lib-vc2019/glfw3.lib)
target_link_libraries(opengl_proj OpenGL::GL)
