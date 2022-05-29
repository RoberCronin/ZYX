#include "Window.hpp"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"

#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

Window* Window::m_Instance = new Window();

void Window::MakeWindowImpl(u_int32_t width, u_int32_t height, std::string title)
{
    m_Width = width;
    m_Height = height;
    m_Title = title;
    InitWindow();
}

GLFWwindow* Window::GetWindowImpl()
{
    return m_Window;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void Window::InitWindow()
{
    // initialize error callback
    glfwSetErrorCallback(glfw_error_callback);

    // initialize glfw
    if (!glfwInit()) std::cout << "Failed to initialize GLFW." << std::endl;

    // configure glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // create the window
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
    if (m_Window == NULL) std::cout << "Failed to create GLFW window." << std::endl;

    // make the OpenGL context current
    glfwMakeContextCurrent(m_Window);

    // enable vsync
    glfwSwapInterval(1);

    // initialize glew
    if (glewInit() != GLEW_OK) std::cout << "glewInit() Failed" << std::endl;
}
