#include "MainLoop.hpp"
#include "Style.hpp"
#include "core/Camera.hpp"
#include "core/Debug.hpp"
#include "core/Time.hpp"
#include "core/Window.hpp"
#include "core/input/Input.hpp"
#include "core/renderer/Shader.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <iostream>

void MainLoop::run()
{
    // Create Window
    Window::MakeWindow(1280, 720, "www");

    // load logo
    GLFWimage logo[1];
    logo[0].pixels = stbi_load("res/textures/logo.png", &logo[0].width, &logo[0].height, 0, 4);

    // set icon to logo
    glfwSetWindowIcon(Window::GetWindow(), 1, logo);

    // free image memory
    stbi_image_free(logo[0].pixels);

    // create shader
    Shader shader("res/shaders/default", Window::GetWindow());
    shader.Bind();

    // create camera
    Camera camera((glm::vec2()));

    // create square
    float vertexArray[] = {
        // position         // color
        0.5f,   0.5f,   0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // bottom left
        100.5f, 0.5f,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // bottom right
        100.5f, 100.5,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f,   100.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top left
    };

    // counter-clockwise order
    unsigned int elementArray[] = {
        0, 1, 2, // top right tri
        0, 2, 3, // bottom left tri
    };

    // create vao
    GLuint vaoID;
    GLCall(glGenVertexArrays(1, &vaoID));
    GLCall(glBindVertexArray(vaoID));

    // create vbo buffer
    GLuint vboID;
    GLCall(glGenBuffers(1, &vboID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
    // upload verticies
    GLCall(glBufferData(GL_ARRAY_BUFFER, 28 * sizeof(float), vertexArray, GL_STATIC_DRAW));

    // create the ebo buffer
    GLuint eboID;
    GLCall(glGenBuffers(1, &eboID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID));
    // upload indicies
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), elementArray, GL_STATIC_DRAW));

    // size of each attribute
    int positionsSize = 3;
    int colorSize = 4;
    int vertexSize = (positionsSize + colorSize) * sizeof(float);

    // position
    GLCall(glVertexAttribPointer(0, positionsSize, GL_FLOAT, GL_FALSE, vertexSize, (const void*)0));
    // color
    GLCall(glVertexAttribPointer(1, colorSize, GL_FLOAT, GL_FALSE, vertexSize, (const void*)(positionsSize * sizeof(float))));

    // imgui
    IMGUI_CHECKVERSION();
    const char* glsl_version = "#version 130";
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // set imgui flags
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

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
    int counter = 0.0f;

    while (!glfwWindowShouldClose(Window::GetWindow()))
    {
        //  poll events
        glfwPollEvents();

        // input
        if (Input::IsKeyPressed(GLFW_KEY_A)) camera.MoveX(-10.0f);
        if (Input::IsKeyPressed(GLFW_KEY_D)) camera.MoveX(10.0f);
        if (Input::IsKeyPressed(GLFW_KEY_W)) camera.MoveY(10.0f);
        if (Input::IsKeyPressed(GLFW_KEY_S)) camera.MoveY(-10.0f);

        // Start imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // imgui windows
        // ImGui::ShowDemoWindow();
        glm::vec4 location = (camera.getProjectionMatrix() * camera.getViewMatrix()) * glm::vec4(100.5f, 100.5, 0.0f, 1.0);
        {
            ImGui::Begin("Debug");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Mouse X: %.1f Mouse Y: %.1f", Input::GetMouseX(), Input::GetMouseY());
            ImGui::Text("x1: %.3f     y1: %.3f     z1: %.3f     w1: %.3f", location.x, location.y, location.z, location.w);
            if (Input::IsKeyPressed(GLFW_KEY_A))
                ImGui::Text("A is being pressed");
            else
                ImGui::Text("A");

            ImGui::Text("Current frame time: %ld", dt);
            ImGui::End();
        }

        // Rendering

        // imgui pre-rendering step
        ImGui::Render();

        // clear screen
        int display_w, display_h;
        glfwGetFramebufferSize(Window::GetWindow(), &display_w, &display_h);
        GLCall(glViewport(0, 0, display_w, display_h));
        GLCall(glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // update uniforms
        shader.Bind(); // have to bind shader before setting uniforms
        shader.SetUniformMat4fv("uProjection", camera.getProjectionMatrix());
        shader.SetUniformMat4fv("uView", camera.getViewMatrix());

        // binding and enabling
        shader.Bind();                        // bind shader
        GLCall(glBindVertexArray(vaoID));     // bind vao
        GLCall(glEnableVertexAttribArray(0)); // enable positions
        GLCall(glEnableVertexAttribArray(1)); // enable colors

        // draw calls
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // unbinding and disabling
        GLCall(glDisableVertexAttribArray(0));
        GLCall(glDisableVertexAttribArray(1));
        GLCall(glBindVertexArray(0));
        shader.UnBind();

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

        // swap buffers
        glfwSwapBuffers(Window::GetWindow());

        endTime = Time::GetTime();
        dt = endTime - beginTime;
        beginTime = endTime;
        counter += 1;
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(Window::GetWindow());
    glfwTerminate();
    glfwSetErrorCallback(NULL);
}
