#include "LinuxInput.hpp"

#include "Window.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

Input* Input::s_Instance = new LinuxInput();

bool LinuxInput::IsKeyPressedImpl(int keycode)
{
    auto window = static_cast<GLFWwindow*>(Window::GetWindow());
    auto state = glfwGetKey(window, keycode);
    return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

bool LinuxInput::IsMouseButtonPressedImpl(int button)
{
    auto window = static_cast<GLFWwindow*>(Window::GetWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> LinuxInput::GetMousePositionImpl()
{
    auto window = static_cast<GLFWwindow*>(Window::GetWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {(float)xpos, (float)ypos};
}

float LinuxInput::GetMouseXImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return x;
}

float LinuxInput::GetMouseYImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return y;
}
