cmake_minimum_required(VERSION 3.17)
project(opengl_abst)

find_package(OpenGL REQUIRED)

set(IMGUI_SOURCES src/vendor/imgui/imgui.cpp src/vendor/imgui/imgui_demo.cpp src/vendor/imgui/imgui_draw.cpp src/vendor/imgui/imgui_impl_glfw.cpp src/vendor/imgui/imgui_impl_opengl3.cpp src/vendor/imgui/imgui_widgets.cpp)
set(SOURCE_FILES src/main.cpp src/Renderer.cpp src/Renderer.hpp src/VertexBuffer.cpp src/VertexBuffer.hpp src/IndexBuffer.cpp src/IndexBuffer.hpp src/VertexArray.cpp src/VertexArray.hpp src/VertexBufferLayout.hpp src/Shader.cpp src/Shader.hpp src/vendor/stb_image/stb_image.hpp src/vendor/stb_image/stb_image.cpp src/Texture.cpp src/Texture.hpp)

add_executable(opengl_abst ${SOURCE_FILES} ${IMGUI_SOURCES})

target_compile_definitions(opengl_abst PRIVATE GLEW_STATIC)
target_include_directories(opengl_abst PRIVATE ${GLEW_DIRECTORY}/include)
target_link_libraries(opengl_abst ${GLEW_DIRECTORY}/lib/Release/Win32/glew32s.lib)

target_include_directories(opengl_abst PRIVATE ${GLFW_DIRECTORY}/include)
target_link_libraries(opengl_abst ${GLFW_DIRECTORY}/lib-vc2019/glfw3.lib)
target_link_libraries(opengl_abst OpenGL::GL)
