#pragma once

#include <string>

class Shader
{
public:
    Shader(const std::string& filepath);
    
    void Bind();
    void UnBind();

private:
    // compiles, links, and returns the program id, to be stored in m_RendererID
    unsigned int CreateShader();
    // returns a string contatining the shader source code
    std::string LoadShader(const std::string& filePath);
    // returns the shader id, or returns 0 if compilation was unsuccessful
    unsigned int CompileShader(unsigned int type, const std::string& source);

    std::string m_FilePath;
    unsigned int m_RendererID;
    Shader(const Shader& other) {}
};
