#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <sys/types.h>

class Window
{
public:
    inline static void MakeWindow(u_int32_t width, u_int32_t height, std::string title) { m_Instance->MakeWindowImpl(width, height, title); }
    inline static GLFWwindow* GetWindow() { return m_Instance->GetWindowImpl(); }

protected:
    virtual void MakeWindowImpl(u_int32_t width, u_int32_t height, std::string title);
    virtual GLFWwindow* GetWindowImpl();

private:
    Window() {}
    Window(Window& window) {}

    void InitWindow();

    int m_Width, m_Height;
    std::string m_Title;
    GLFWwindow* m_Window;

    static Window* m_Instance;
};
