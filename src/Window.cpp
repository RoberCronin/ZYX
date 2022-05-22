#include "Window.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

Window::Window(u_int32_t width, u_int32_t height, std::string title)
    : m_Width(width)
    , m_Height(height)
    , m_Title(title)
{
}

Window::Window()
    : m_Width(1920)
    , m_Height(1080)
    , m_Title("window")
{
}

void Window::run()
{
    init();
    loop();
}

void Window::init()
{
    // initialize glfw
    if (!glfwInit()) std::cout << "Failed to initialize GLFW." << std::endl;

    // confifure glfw
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // create the window
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
    if (m_Window == nullptr) std::cout << "Failed to create GLFW window." << std::endl;

    // make the OpenGL context current
    glfwMakeContextCurrent(m_Window);

    // enable vsync
    glfwSwapInterval(1);

    // make the window visible
    glfwShowWindow(m_Window);
}

void Window::loop()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        // poll events
        glfwPollEvents();

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_Window);
    }
}
