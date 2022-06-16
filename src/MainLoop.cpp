#include "MainLoop.hpp"
#include "Style.hpp"

#include "core/include.hpp"
#include "core/input/Input.hpp"
#include "core/renderer/ElementBufferObject.hpp"
#include "core/renderer/VertexArrayObject.hpp"
#include "core/renderer/entity.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <iostream>
#include <vector>

glm::vec2 newPos(const entity& ent, float prevXDelta, float prevYDelta, const unsigned int screenWidth, const unsigned int screenHeight)
{
    glm::vec2 updatedPos(prevXDelta, prevYDelta);

    if (ent.GetPosX() < 0 && prevXDelta > 0) updatedPos.x *= -1;
    if (ent.GetPosX() + ent.GetWidth() > screenWidth && prevXDelta < 0) updatedPos.x *= -1;

    return updatedPos;
}

void MainLoop::run()
{
    // Create Window
    const unsigned int screenWidth = 1280;
    const unsigned int screenHeight = 720;
    Window::MakeWindow(screenWidth, screenHeight, "ZYX");

    // create shader
    Shader shader("res/shaders/default", Window::GetWindow());
    shader.Bind();

    // load logo
    GLFWimage logo[1];
    logo[0].pixels = stbi_load("res/textures/logo.png", &logo[0].width, &logo[0].height, 0, 4);

    // // load texture
    // Texture texture("res/textures/testTexture.png", 0);
    // texture.Bind();

    // set icon to logo
    glfwSetWindowIcon(Window::GetWindow(), 1, logo);

    // free image memory
    stbi_image_free(logo[0].pixels);

    // create camera
    Camera camera((glm::vec2()), screenWidth, screenHeight);

    std::vector<entity> entities;

    entities.push_back(entity("res/textures/testTexture.png", 100, 100, 0, 0));
    entities.push_back(entity("res/textures/testTexture.png", 100, 100, 400, 100));
    entities.push_back(entity("res/textures/testTexture.png", 100, 100, 900, 70));
    entities.push_back(entity("res/textures/testTexture.png", 100, 100, Input::GetMouseX(), Input::GetMouseY()));

    Renderer renderer;

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
    long frameTimeStart = Time::GetTime();
    long frameTimeEnd = Time::GetTime();
    long frameTime;
    long dt = 0;
    float frameRate = 60.0f;
    bool limitFramerate = true;
    float XDelta = 5.0;
    float YDelta = 5.0;

    const float yMoveDelta = 720.0 / 100.0;
    const float xMoveDelta = 1280.0 / 100.0;

    while (!glfwWindowShouldClose(Window::GetWindow()))
    {
        // start frame time timer
        long frameTimeStart = Time::GetTime();

        //  poll events
        glfwPollEvents();

        // Start imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // imgui windows
        // ImGui::ShowDemoWindow();
        glm::vec4 location = (camera.getProjectionMatrix() * camera.getViewMatrix()) * glm::vec4(100.5f, 100.5, 0.0f, 1.0);
        {
            ImGui::Begin("Debug");
            ImGui::SliderFloat("Framerate", &frameRate, 1.0f, 200.0f);
            ImGui::Checkbox("Disable Framelimiter", &limitFramerate);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Mouse X: %.1f Mouse Y: %.1f", Input::GetMouseX(), Input::GetMouseY());
            ImGui::Text("x1: %.3f     y1: %.3f     z1: %.3f     w1: %.3f", location.x, location.y, location.z, location.w);
            if (Input::IsKeyPressed(GLFW_KEY_A))
                ImGui::Text("A is being pressed");
            else
                ImGui::Text("A");

            ImGui::Text("Current frame time: %ld", frameTime);
            ImGui::End();
        }

        // update scene

        if (entities[1].GetPosX() + entities[1].GetWidth() + XDelta > screenWidth) XDelta = -5.0f;
        if (entities[1].GetPosX() + XDelta < 0) XDelta = 5.0f;

        if (entities[1].GetPosY() + entities[1].GetHeight() + YDelta > screenHeight) YDelta = -5.0f;
        if (entities[1].GetPosY() + YDelta < 0) YDelta = 5.0f;

        entities[1].Move(entities[1].GetPosX() + XDelta, entities[1].GetPosY() + YDelta);

        // update verticies
        // vbo.UploadVerticies(vertexArray);

        // Rendering
        renderer.StartScene(&camera, &shader);

        // imgui pre-rendering step
        ImGui::Render();

        // clear screen
        int display_w, display_h;
        glfwGetFramebufferSize(Window::GetWindow(), &display_w, &display_h);
        GLCall(glViewport(0, 0, display_w, display_h));
        GLCall(glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // setup scene
        // renderer.Submit(&meshMain);

        entities[0].Move(Input::GetMouseX(), Input::GetMouseY());
        for (int i = 0; i < entities.size(); i++)
        {
            renderer.Submit(&entities[i]);
            entities[i].UpdateVerts();
        }

        // update uniforms

        // binding and enabling

        // draw calls
        renderer.EndScene();
        renderer.Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // unbinding and disabling

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

        // calculate frame time
        long frameTimeEnd = Time::GetTime();
        frameTime = frameTimeEnd - frameTimeStart;
        endTime = Time::GetTime();

        // calculate delta time
        dt = endTime - beginTime;
        beginTime = endTime;
        if (limitFramerate) Framerate::Sleep(frameRate, frameTime);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(Window::GetWindow());
    glfwTerminate();
    glfwSetErrorCallback(NULL);
}
