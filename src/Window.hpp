#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <sys/types.h>

class Window
{
public:
    Window(u_int32_t width, u_int32_t height, std::string title);
    Window();

    inline GLFWwindow* GetContext() const { return m_Window; }

private:
    void InitWindow();

    int m_Width, m_Height;
    std::string m_Title;
    GLFWwindow* m_Window;
};
