#include <iostream>

#include "Window.hpp"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_opengl3.h"
#include "external/imgui/imgui_internal.h"

int main()
{
    Window window(1920, 1080, "www");

    window.run();

    return 0;
}
