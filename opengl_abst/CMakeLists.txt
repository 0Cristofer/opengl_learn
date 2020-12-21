cmake_minimum_required(VERSION 3.17)
project(opengl_abst)

find_package(OpenGL REQUIRED)

add_executable(opengl_abst src/main.cpp src/Renderer.cpp src/Renderer.hpp src/VertexBuffer.cpp src/VertexBuffer.hpp src/IndexBuffer.cpp src/IndexBuffer.hpp)

target_compile_definitions(opengl_abst PRIVATE GLEW_STATIC)
target_include_directories(opengl_abst PRIVATE ${GLEW_DIRECTORY}/include)
target_link_libraries(opengl_abst ${GLEW_DIRECTORY}/lib/Release/Win32/glew32s.lib)

target_include_directories(opengl_abst PRIVATE ${GLFW_DIRECTORY}/include)
target_link_libraries(opengl_abst ${GLFW_DIRECTORY}/lib-vc2019/glfw3.lib)
target_link_libraries(opengl_abst OpenGL::GL)
