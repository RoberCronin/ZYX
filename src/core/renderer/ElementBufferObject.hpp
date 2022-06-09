#pragma once

#include "core/include.hpp"

#include <vector>

class ElementBufferObject
{
public:
    ElementBufferObject(std::vector<unsigned int> indicies);

    void Bind();
    void Unbind();

private:
    GLuint m_EboID;
};
