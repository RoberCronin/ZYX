cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME "GameEngine")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME} VERSION 1.0.0)
link_directories(${CMAKE_BINARY_DIR})

include_directories(
    src/
    external/
)

add_executable(${PROJECT_NAME}
src/main.cpp
src/core/Window.cpp
src/MainLoop.cpp
src/core/input/LinuxInput.cpp
src/core/Time.cpp
external/imgui/imgui_demo.cpp
external/imgui/imgui_draw.cpp
external/imgui/imgui_impl_glfw.cpp
external/imgui/imgui_impl_opengl3.cpp
external/imgui/imgui_tables.cpp
external/imgui/imgui_widgets.cpp
external/imgui/imgui.cpp
)

target_link_libraries(${PROJECT_NAME}
    GLEW GL glfw 
)

add_compile_definitions(GLEW_STATIC)
