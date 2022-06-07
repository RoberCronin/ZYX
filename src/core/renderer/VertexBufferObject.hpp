#pragma once

#include "core/include.hpp"

#include <cstddef>
#include <vector>

// used when verteicies will be updated every frame
// expects a vector
template <typename type> class DynamicVertexBufferObject
{
public:
    DynamicVertexBufferObject(size_t bufferSize);

    void UploadVerticies(const std::vector<type>& verticies);

    void Bind();
    void Unbind();

private:
    GLuint m_VboID;
    unsigned int m_BufferSize;
};

// used when verticies will not change
// verticies uploaded to gpu in constructor
template <typename type> class StaticVertexBufferObject
{
public:
    StaticVertexBufferObject(std::vector<type> verticies);

    void Bind();
    void Unbind();

private:
    GLuint m_VboID;
};

template <typename type>
StaticVertexBufferObject<type>::StaticVertexBufferObject(std::vector<type> verticies)
    : m_VboID(0)
{
    // get id
    GLCall(glGenBuffers(1, &m_VboID));

    Bind();
    // upload verticies
    GLCall(glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(type), verticies.cbegin(), GL_STATIC_DRAW));
}

template <typename type> void StaticVertexBufferObject<type>::Bind()
{

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VboID));
}

template <typename type> void StaticVertexBufferObject<type>::Unbind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

template <typename type> DynamicVertexBufferObject<type>::DynamicVertexBufferObject(size_t bufferCount)
{
    GLCall(glGenBuffers(1, &m_VboID));
    m_BufferSize = bufferCount * sizeof(type);

    Bind();
    // create buffer that will have verticies filled in later
    GLCall(glBufferData(GL_ARRAY_BUFFER, m_BufferSize, nullptr, GL_DYNAMIC_DRAW));
}

template<typename type>
void DynamicVertexBufferObject<type>::UploadVerticies(const std::vector<type>& verticies)
{
    Bind();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_BufferSize, (const void *)&verticies.cbegin()[0]));
}

template <typename type> void DynamicVertexBufferObject<type>::Bind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VboID));
}

template <typename type> void DynamicVertexBufferObject<type>::Unbind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
