#include "core/include.hpp"

StaticVertexBufferObject::StaticVertexBufferObject(std::vector<float> verticies)
    : m_VboID(0)
{
    // get id
    GLCall(glGenBuffers(1, &m_VboID));

    Bind();
    // upload verticies
    GLCall(glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), (const void*)&verticies.cbegin()[0], GL_STATIC_DRAW));
}

void StaticVertexBufferObject::Bind()
{

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VboID));
}

void StaticVertexBufferObject::Unbind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

DynamicVertexBufferObject::DynamicVertexBufferObject(size_t bufferCount)
{
    GLCall(glGenBuffers(1, &m_VboID));
    m_BufferSize = bufferCount * sizeof(float);

    Bind();
    // create buffer that will have verticies filled in later
    GLCall(glBufferData(GL_ARRAY_BUFFER, m_BufferSize, nullptr, GL_DYNAMIC_DRAW));
}

void DynamicVertexBufferObject::UploadVerticies(const std::vector<float>& verticies)
{
    Bind();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_BufferSize, (const void*)&verticies.cbegin()[0]));
}

void DynamicVertexBufferObject::Bind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VboID));
}

void DynamicVertexBufferObject::Unbind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
