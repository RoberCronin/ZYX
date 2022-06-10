#pragma once

#include <GL/glew.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>

class ElementBufferObject
{
public:
    ElementBufferObject(std::vector<unsigned int> indicies);

    void Bind();
    void Unbind();

    unsigned int GetCount();

private:
    GLuint m_EboID;
    unsigned int m_Count;
};
