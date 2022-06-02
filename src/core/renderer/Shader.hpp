#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
    Shader(const std::string& filepath, GLFWwindow* window);

    void Bind();
    void UnBind();

    unsigned int GetRendererID() { return m_RendererID; }

    // single number uniforms
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);

    // float vector uniforms
    void SetUniform2f(const std::string& name, float v0, float v1);
    void SetUniform3f(const std::string& name, float v0, float v1, float v2);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    // matrix uniforms
    void SetUniformMat2fv(const std::string& name, const glm::mat2& matrix);
    void SetUniformMat3fv(const std::string& name, const glm::mat3& matrix);
    void SetUniformMat4fv(const std::string& name, const glm::mat4& matrix);

private:
    // compiles, links, and returns the program id, to be stored in m_RendererID
    unsigned int CreateShader();
    // returns a string contatining the shader source code
    std::string LoadShader(const std::string& filePath);
    // returns the shader id, or returns 0 if compilation was unsuccessful
    unsigned int CompileShader(unsigned int type, const std::string& source);

    // returns uniform location, and checks if uniform exists
    int GetUniformLocation(const std::string& name);

    std::string m_FilePath;
    unsigned int m_RendererID;
    GLFWwindow* m_Window;
    Shader(const Shader& other) {}
};
