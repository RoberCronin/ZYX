#include "MainLoop.hpp"
#include "Style.hpp"
#include "core/Time.hpp"
#include "core/Window.hpp"
#include "core/input/Input.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <iostream>

void MainLoop::run()
{
    // Create Window
    Window::MakeWindow(1920, 1080, "www");

    // imgui
    IMGUI_CHECKVERSION();
    const char* glsl_version = "#version 130";
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // set imgui flags
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

    // ImGui::StyleColorsDark();
    Style(io);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // init imgui implemtations
    ImGui_ImplGlfw_InitForOpenGL(Window::GetWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // main loop variables
    long beginTime = Time::GetTime();
    long endTime = Time::GetTime();
    long dt = 0;

    while (!glfwWindowShouldClose(Window::GetWindow()))
    {
        // poll events
        glfwPollEvents();

        // Start imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // imgui windows
        // ImGui::ShowDemoWindow();
        {
            ImGui::Begin("Debug");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Mouse X: %.1f Mouse Y: %.1f", Input::GetMouseX(), Input::GetMouseY());
            if (Input::IsKeyPressed(GLFW_KEY_A))
                ImGui::Text("A is being pressed");
            else
                ImGui::Text("A");

            ImGui::Text("Current frame time: %ld", dt);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(Window::GetWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(Window::GetWindow());

        endTime = Time::GetTime();
        dt = endTime - beginTime;
        beginTime = endTime;
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(Window::GetWindow());
    glfwTerminate();
    glfwSetErrorCallback(NULL);
}
