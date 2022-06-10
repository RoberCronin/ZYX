#include "Mesh.hpp"

Mesh::Mesh(DynamicVertexBufferObject* vbo, VertexArrayObject* vao, ElementBufferObject* ebo, Texture* texture)
    : m_VboPointer(vbo)
    , m_VaoPointer(vao)
    , m_EboPointer(ebo)
    , m_Texture(texture)
{
}

void Mesh::Bind()
{
    m_VboPointer->Bind();
    m_VaoPointer->Bind();
    m_EboPointer->Bind();
    m_Texture->Bind();
}

void Mesh::Unbind()
{
    m_VboPointer->Unbind();
    m_VaoPointer->Unbind();
    m_EboPointer->Unbind();
    m_Texture->Unbind();
}

unsigned int Mesh::GetIndiciesCount()
{
    return m_EboPointer->GetCount();
}
