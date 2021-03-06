#pragma once

#include <GL/glew.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>

class VertexArrayObject
{
public:
    VertexArrayObject();

    // adds a vertex attribute to stack, valid types are:
    // GL_BYTE
    // GL_UNSIGNED_BYTE
    // GL_SHORT
    // GL_UNSIGNED_SHORT
    // GL_INT
    // GL_UNSIGNED_INT
    // GL_FLOAT
    // GL_DOUBLE
    void AddVertexAttribute(const int& count, const int& type);
    // calls glVertexAttribPointer for each attribute
    void SetVertexAttributes();

    void Bind();
    void Unbind();

    inline unsigned int GetCount() const; 

private:
    struct VertexAttribute
    {
        unsigned int index;
        int componentCount;
        int type;
        // bool normalized; // always use GL_FALSE so don't need to store if it is normalized
        //  unsigned int stride; // stride is the same for all vertex attributes, so only need to calculate it once
        int pointer;
    };

    int CalculateStride();
    int CalculateOffset();
    void ValidateVertexAttributeType(const int& type);
    void ValidateVertexAttributeCount(const int& count);
    int SizeOfGLType(const int& type);

    GLuint m_VaoID;

    std::vector<VertexAttribute> m_VertexAttributes;
};
