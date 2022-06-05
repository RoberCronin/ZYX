#pragma once

#include "core/include.hpp"

#include <vector>

class VertexArrayObject
{
public:
    VertexArrayObject();

    void AddVertexAttribute(const int& count, const int& type);
    void SetVertexAttributes();

    void Bind();
    void Unbind();

private:
    struct VertexAttribute
    {
        unsigned int index;
        int componentCount;
        int type;
        // bool normalized; // always use GL_FALSE so don't need to store if it is normalized
        //  unsigned int stride;
        int pointer;
    };

    int CalculateStride();
    int CalculateOffset();
    void ValidateVertexAttributeType(const int& type);
    int SizeOfGLType(const int& type);

    GLuint m_VaoID;

    std::vector<VertexAttribute> m_VertexAttributes;
};
