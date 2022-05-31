#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& filepath);

    void Bind();
    void UnBind();

    void SetUniform1i(const std::string& name, int value);
    void SetUniform2f(const std::string& name, float v0, float v1);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4 matrix);

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
    Shader(const Shader& other) {}
};
