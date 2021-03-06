#include "core/include.hpp"

#include <fstream>
#include <iostream>

Shader::Shader(const std::string& filepath, GLFWwindow* window)
    : m_FilePath(filepath)
    , m_RendererID(0)
    , m_Window(window)
{
    // links and compiles the shaders
    m_Bound = false;
    m_RendererID = CreateShader();
}

void Shader::Bind()
{
    if (!m_Bound)
    {
        glUseProgram(m_RendererID);
        m_Bound = true;
    }
}

void Shader::UnBind()
{
    m_Bound = false;
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    Bind();
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    Bind();
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform2f(const std::string& name, float v0, float v1)
{
    Bind();
    GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    Bind();
    GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    Bind();
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat2fv(const std::string& name, const glm::mat2& matrix)
{
    Bind();
    GLCall(glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniformMat3fv(const std::string& name, const glm::mat3& matrix)
{
    Bind();
    GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniformMat4fv(const std::string& name, const glm::mat4& matrix)
{
    Bind();
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetTexture(std::string name, int slot)
{
    Bind();
    GLCall(glUniform1i(GetUniformLocation(name), slot));
}

unsigned int Shader::CreateShader()
{
    // creates the shader program
    unsigned int program = glCreateProgram();

    // loads the shaders into shader source strings
    std::string vertexSource = LoadShader(m_FilePath + ".vs");
    std::string fragmentSource = LoadShader(m_FilePath + ".fs");

    // compiles the shaders
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // attach shaders to program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    // link program to gpu
    glLinkProgram(program);

    glValidateProgram(program);

    // delete shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    std::cout << "Shader linking done\n";

    return program;
}

std::string Shader::LoadShader(const std::string& filePath)
{
    // open source file
    std::ifstream file;
    file.open(filePath.c_str());

    // stores the output string
    std::string output;
    // stores the current line
    std::string line;

    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << filePath << std::endl;
    }

    return output;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    // get a shader id
    unsigned int id = glCreateShader(type);
    // have to get address of source string since gl is written in C
    const char* src = source.c_str();
    // store shader code bytes in shader object
    glShaderSource(id, 1, &src, nullptr);
    // compile the shader
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    // check if shader compiled correctly
    if (result == GL_FALSE)
    {
        // get length of error message
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        // allocate space for error message
        char* message = (char*)alloca(length * sizeof(char));

        // output error message
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader.\n";
        std::cout << message << std::endl;
        glDeleteShader(id);

        return 0;
    }

    std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader compilation done\n";
    return id;
}

int Shader::GetUniformLocation(const std::string& name)
{
    GLCall(GLint location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) std::cout << "Warning: uniform '" << name << "' doesn't exist." << std::endl;
    return location;
}
