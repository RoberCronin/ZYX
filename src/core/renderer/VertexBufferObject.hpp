#pragma once

#include <GL/glew.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <vector>

// used when verteicies will be updated every frame
// expects a vector
class DynamicVertexBufferObject
{
public:
    DynamicVertexBufferObject(size_t bufferSize);

    void UploadVerticies(const std::vector<float>& verticies);

    void Bind();
    void Unbind();

private:
    GLuint m_VboID;
    unsigned int m_BufferSize;
};

// used when verticies will not change
// verticies uploaded to gpu in constructor
class StaticVertexBufferObject
{
public:
    StaticVertexBufferObject(std::vector<float> verticies);
    void Bind();
    void Unbind();

private:
    GLuint m_VboID;
};
